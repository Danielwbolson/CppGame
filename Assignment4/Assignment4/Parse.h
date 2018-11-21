
#ifndef PARSE_H_
#define PARSE_H_

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "Scene.h"
#include "Map.h"

#include "Component.h"
#include "MeshRenderer.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "Camera.h"
#include "PlayerMovement.h"

#include "Mesh.h"
#include "GameObject.h"
#include "Material.h"

#include "Light.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "AmbientLight.h"

#include "Vec3.h"

struct vertData {
    int v;
    int uv;
    int n;

    bool operator==(const vertData& rhs) {
        if (v != rhs.v) { return false; }
        if (uv != rhs.uv) { return false; }
        if (n != rhs.n) { return false; }

        return true;
    }
};

static void ObjParse(Mesh& mesh, const std::string fileName) {
    FILE *fp;
    char line[1024]; //Assumes no line is longer than 1024 characters!

    // open the file containing the scene description
    fp = fopen(fileName.c_str(), "r");

    // check for errors in opening the file
    if (fp == NULL) {
        fprintf(stderr, "Can't open file '%s'\n", fileName.c_str());
    }

    std::vector<Vec3> rawVerts;
    std::vector<Vec3> rawNormals;
    std::vector<Vec2> rawUvs;

    std::vector<Vec3> verts;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;
    std::vector<unsigned short> indices;

    std::vector<vertData> vertMap;
    int nextIndex = 0;
    //Loop through reading each line
    while (fgets(line, 1024, fp)) { //Assumes no line is longer than 1024 characters!
        if (line[0] == '#') {
            //fprintf(stderr, "Skipping comment: %s", line);
            continue;
        }

        char command[1024];
        int fieldsRead = sscanf(line, "%s ", command); //Read first word in the line (i.e., the command type)

        if (fieldsRead < 1) { //No command read
            //Blank line
            continue;
        }

        if (line[0] == '#') {
            //fprintf(stderr, "Skipping comment: %s", line);
            continue;
        }

        // vertex
        if (strcmp(command, "v") == 0) {
            Vec3 v;

            sscanf(line, "v %f %f %f", &v.x, &v.y, &v.z);
            rawVerts.push_back(v);
        }
        // uvs
        else if (strcmp(command, "vt") == 0) {
            Vec2 uv;

            sscanf(line, "vt %f %f", &uv.x, &uv.y);
            rawUvs.push_back(uv);
        }
        // normals
        else if (strcmp(command, "vn") == 0) {
            Vec3 n;

            sscanf(line, "vn %f %f %f", &n.x, &n.y, &n.z);
            rawNormals.push_back(n.Normalize());
        }
        // face
        else if (strcmp(command, "f") == 0) {
            int vert_info[3][3];

            sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &vert_info[0][0], &vert_info[0][1], &vert_info[0][2],
                &vert_info[1][0], &vert_info[1][1], &vert_info[1][2],
                &vert_info[2][0], &vert_info[2][1], &vert_info[2][2]);
            // https://stackoverflow.com/questions/23349080/opengl-index-buffers-difficulties/23356738#23356738

            for (int i = 0; i < 3; i++) {
                vertData temp_vert = vertData{
                    temp_vert.v = vert_info[i][0],
                    temp_vert.uv = vert_info[i][1],
                    temp_vert.n = vert_info[i][2]
                };

                bool exists = false;
                for (int j = 0; j < vertMap.size(); j++) {
                    if (temp_vert == vertMap[j]) {
                        exists = true;
                        indices.push_back(j);
                        break;
                    }
                }

                if (!exists) {
                    indices.push_back(nextIndex);
                    vertMap.push_back(temp_vert);
                    nextIndex++;
                    verts.push_back(rawVerts[temp_vert.v - 1]);
                    uvs.push_back(rawUvs[temp_vert.uv - 1]);
                    normals.push_back(rawNormals[temp_vert.n - 1]);
                }
            }
        }
        else { continue; }
    }

    mesh.SetPositions(verts);
    mesh.SetNormals(normals);
    mesh.SetUvs(uvs);
    mesh.SetIndices(indices);

    rawVerts.clear();
    rawVerts.empty();
    rawNormals.clear();
    rawNormals.empty();
    rawUvs.clear();
    rawUvs.empty();

    verts.clear();
    verts.empty();
    normals.clear();
    normals.empty();
    uvs.clear();
    uvs.empty();
    indices.clear();
    indices.empty();
}

static Scene SceneParse(Scene& scene, std::string fileName) {
    FILE *fp;
    char line[1024]; //Assumes no line is longer than 1024 characters!

    // open the file containing the scene description
    fp = fopen(fileName.c_str(), "r");

    // check for errors in opening the file
    if (fp == NULL) {
        fprintf(stderr, "Can't open file '%s'\n", fileName.c_str());
    }

    Material currMaterial;
    GameObject* currGameObject = new GameObject();
    Mesh currMesh;
    int window_width, window_height;

    //Loop through reading each line
    while (fgets(line, 1024, fp)) { //Assumes no line is longer than 1024 characters!
        if (line[0] == '#') {
            //fprintf(stderr, "Skipping comment: %s", line);
            continue;
        }

        char command[1024];
        int fieldsRead = sscanf(line, "%s ", command); //Read first word in the line (i.e., the command type)

        if (fieldsRead < 1) { //No command read
            //Blank line
            continue;
        }

        if (strcmp(command, "aspect_ratio") == 0) {
            sscanf(line, "aspect_ratio %d %d", &window_width, &window_height);

            scene.window_width = window_width;
            scene.window_height = window_height;
        }
        else if (strcmp(command, "gameObject") == 0) {
            currGameObject = new GameObject();
            char name[1024];

            sscanf(line, "gameObject %s", name);
            currGameObject->name = name;
        }
        else if (strcmp(command, "component") == 0) {
            char type[1024];

            sscanf(line, "component %s", &type);

            if (strcmp(type, "boxCollider") == 0) {
                Vec3 pos;
                float width, height;
                int dynamic, isTrigger;
                sscanf(line, "component boxCollider %f %f %f %f %f %d %d", 
                    &pos.x, &pos.y, &pos.z, &width, &height, &dynamic, &isTrigger);
                if (currGameObject)
                    currGameObject->AddComponent(new BoxCollider(pos, width, height, dynamic, isTrigger));
            }
            else if (strcmp(type, "sphereCollider") == 0) {
                Vec3 pos;
                float radius;
                int dynamic, isTrigger;

                sscanf(line, "component sphereCollider %f %f %f %f %d %d",
                    &pos.x, &pos.y, &pos.z, &radius, &dynamic, &isTrigger);

                if (currGameObject)
                    currGameObject->AddComponent(new SphereCollider(pos, radius, dynamic, isTrigger));
            }
            else if (strcmp(type, "camera") == 0) {
                float lax, lay, laz;
                float ux, uy, uz;
                float fov, np, fp;

                sscanf(line, "component camera %f %f %f %f %f %f %f %f %f",
                    &lax, &lay, &laz, &ux, &uy, &uz, &fov, &np, &fp);

                if (currGameObject) {
                    currGameObject->AddComponent(new Camera(
                        Vec3(lax, lay, laz),
                        Vec3(ux, uy, uz).Normalize(),
                        window_width,
                        window_height,
                        fov, np, fp));
                }
            }
            else if (strcmp(type, "meshRenderer") == 0) {
                if (currGameObject)
                    currGameObject->AddComponent(new MeshRenderer(currMesh, currMaterial));
            }
            else if (strcmp(type, "playerMovement") == 0) {
                float speed;

                sscanf(line, "component playerMovement %f", &speed);

                if (currGameObject)
                    currGameObject->AddComponent(new PlayerMovement(speed));
            }
            else if (strcmp(type, "transform") == 0) {
                if (currGameObject)
                    currGameObject->AddComponent(new Transform());
            }
            else { continue; }
        }
        else if (strcmp(command, "endGameObject") == 0) {
            scene.gameObjects.push_back(currGameObject);
        }
        else if (strcmp(command, "mesh") == 0) {
            char filename[1024];

            sscanf(line, "mesh %s", &filename);

            ObjParse(currMesh, filename);
            currMesh.name = currGameObject->name;
        }
        else if (strcmp(command, "material") == 0) { // If the command is a material
            float ar, ag, ab; // ambient coefficients
            float dr, dg, db; // diffuse coefficients
            float sr, sg, sb; // specular coefficients

            sscanf(line, "material %f %f %f %f %f %f %f %f %f\n",
                &ar, &ag, &ab, &dr, &dg, &db, &sr, &sg, &sb);

            currMaterial = Material(Vec3(ar, ag, ab), Vec3(dr, dg, db), Vec3(sr, sg, sb));
        }
        else if (strcmp(command, "directional_light") == 0) { // If the command is a directional light
            float r, g, b, dx, dy, dz;
            sscanf(line, "directional_light %f %f %f %f %f %f",
                &r, &g, &b, &dx, &dy, &dz);

            scene.lights.push_back(new DirectionalLight(Vec3(r, g, b), Vec3(dx, dy, dz).Normalize()));
        }
        else if (strcmp(command, "spot_light") == 0) { // If the command is a point_light
            float r, g, b;
            float px, py, pz;
            float dx, dy, dz;
            float angle1, angle2;
            sscanf(line, "spot_light %f %f %f %f %f %f %f %f %f %f %f",
                &r, &g, &b, &px, &py, &pz, &dx, &dy, &dz, &angle1, &angle2);

            scene.lights.push_back(new SpotLight(Vec3(r, g, b), Vec3(px, py, pz), Vec3(dx, dy, dz).Normalize(), angle1, angle2));
        }
        else if (strcmp(command, "point_light") == 0) { // If the command is a spot_light
            float r, g, b, x, y, z;
            sscanf(line, "point_light %f %f %f %f %f %f",
                &r, &g, &b, &x, &y, &z);

            scene.lights.push_back(new PointLight(Vec3(r, g, b), Vec3(x, y, z)));
        }
        else if (strcmp(command, "ambient_light") == 0) { // If the command is a ambient_light
            float r, g, b;
            sscanf(line, "ambient_light %f %f %f", &r, &g, &b);

            scene.lights.push_back(new AmbientLight(Vec3(r, g, b)));
        }
        else {
            fprintf(stderr, "WARNING. Do not know command: %s\n", command);
        }
    }
    return scene;
}

static Map MapParse(Map& map, std::string fileName, Scene* s) {
    FILE *fp;
    char line[1024]; //Assumes no line is longer than 1024 characters!

    // open the file containing the scene description
    fp = fopen(fileName.c_str(), "r");

    // check for errors in opening the file
    if (fp == NULL) {
        fprintf(stderr, "Can't open file '%s'\n", fileName.c_str());
    }

    int i = 0;
    int width, height;
    //Loop through reading each line
    while (fgets(line, 1024, fp)) { //Assumes no line is longer than 1024 characters!
        if (line[0] == '#') {
            //fprintf(stderr, "Skipping comment: %s", line);
            continue;
        }

        int fieldsRead; char row[100];

        // Bounds of grid
        int temp_width, temp_height;
        if ((fieldsRead = sscanf(line, "%d %d", &temp_width, &temp_height)) == 2) {
            width = temp_width;
            height = temp_height;
            map.Setup(width, height);
        }
        // Grid entries
        else if ((fieldsRead = sscanf(line, "%s", row)) == 1) {
            for (int j = 0; j < width; j++) {
                switch (row[j]) {
                case '0' :
                    map.layout.push_back(empty);
                    break;
                case 'W' :
                    map.layout.push_back(wall);
                    break;
                case 'S' :
                    map.layout.push_back(start);
                    break;
                case 'G' :
                    map.layout.push_back(goal);
                    break;
                case 'A' :
                    map.layout.push_back(door1);
                    break;
                case 'B' :
                    map.layout.push_back(door2);
                    break;
                case 'C' :
                    map.layout.push_back(door3);
                    break;
                case 'D' :
                    map.layout.push_back(door4);
                    break;
                case 'E' :
                    map.layout.push_back(door5);
                    break;
                case 'a' :
                    map.layout.push_back(key1);
                    break;
                case 'b' :
                    map.layout.push_back(key2);
                    break;
                case 'c' :
                    map.layout.push_back(key3);
                    break;
                case 'd' :
                    map.layout.push_back(key4);
                    break;
                case 'e' :
                    map.layout.push_back(key5);
                    break;
                default:
                    break;
                }
            }
            i++;
        }
        else { continue; }

    }

    s->instances.reserve(map.layout.size());
    // Create actual grid
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            bool flag = true;
            GameObject* g = new GameObject();
            Transform* t = new Transform();
            switch (map.layout[map.index(i, j)]) {
            case empty:
                flag = false;
                break;
            case wall: {
                g = new GameObject(*(s->FindGameObject("wall")));
                break;
            }
            case start: {
                g = new GameObject(*(s->FindGameObject("player")));
                break;
            }
            case goal: {
                flag = false;
                break;
            }
            case door1: {
                g = new GameObject(*(s->FindGameObject("door1")));
                break;
            }
            case door2: {
                g = new GameObject(*(s->FindGameObject("door2")));
                break;
            }
            case door3: {
                g = new GameObject(*(s->FindGameObject("door3")));
                break;
            }
            case door4: {
                g = new GameObject(*(s->FindGameObject("door4")));
                break;
            }
            case door5: {
                g = new GameObject(*(s->FindGameObject("door5")));
                break;
            }
            case key1: {
                g = new GameObject(*(s->FindGameObject("key1")));
                break;
            }
            case key2: {
                g = new GameObject(*(s->FindGameObject("key2")));
                break;
            }
            case key3: {
                g = new GameObject(*(s->FindGameObject("key3")));
                break;
            }
            case key4: {
                g = new GameObject(*(s->FindGameObject("key4")));
                break;
            }
            case key5: {
                g = new GameObject(*(s->FindGameObject("key5")));
                break;
            }
            default:
                flag = false;
                break;
            }

            if (flag) {
                t = g->GetTransform();
                t->SetPosition(glm::vec3((float)s->cube_width * j, 0, (float)s->cube_width * i));
                for (int i = 0; i < g->components.size(); i++) {
                    g->components[i]->gameObject = g;
                }
                s->instances.push_back(g);
            }
        }
    }
    return map;
}

#endif