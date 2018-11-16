
#ifndef PARSE_H_
#define PARSE_H_

#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "Scene.h"
#include "Map.h"

#include "Camera.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "AmbientLight.h"

#include "Vec3.h"

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

    //Loop through reading each line
    while (fgets(line, 1024, fp)) { //Assumes no line is longer than 1024 characters!
        if (line[0] == '#') {
            //fprintf(stderr, "Skipping comment: %s", line);
            continue;
        }

        char command[100];
        int fieldsRead = sscanf(line, "%s ", command); //Read first word in the line (i.e., the command type)

        if (fieldsRead < 1) { //No command read
            //Blank line
            continue;
        }

        if (strcmp(command, "camera") == 0) { //If the command is a camera
            float px, py, pz;
            float dx, dy, dz;
            float ux, uy, uz;
            float ha;
            sscanf(line, "camera %f %f %f %f %f %f %f %f %f %f",
                &px, &py, &pz, &dx, &dy, &dz, &ux, &uy, &uz, &ha);
            
            Vec3 right = Vec3(ux, uy, uz).Cross(Vec3(dx, dy, dz)).Normalize();
            Vec3 up = Vec3(dx, dy, dz).Cross(Vec3(right.x, right.y, right.z)).Normalize();

            Camera cam = Camera(Vec3(px, py, pz), Vec3(dx, dy, dz).Normalize(), up, ha);
            scene.camera = cam;
        }
        else if (strcmp(command, "film_resolution") == 0) { // If the command is a film_resolution command
            int width, height;
            sscanf(line, "film_resolution %d %d", &width, &height);

            scene.width = width;
            scene.height = height;
        }
        else if (strcmp(command, "output_image") == 0) { // If the command is an output_image command
            char outFile[1024];
            sscanf(line, "output_image %s", outFile);

            scene.image_path = outFile;
        }
        //else if (strcmp(command, "max_vertices") == 0) { // If the command is the number of max vertices
        //    int n;
        //    sscanf(line, "max_vertices %d", &n);

        //    scene.max_vertices = n;
        //    scene.vertices.reserve(n);
        //}
        //else if (strcmp(command, "max_normals") == 0) { // IF the command is the number of max normals
        //    int n;
        //    sscanf(line, "max_normals %d", &n);

        //    scene.max_normals = n;
        //    scene.normals.reserve(n);
        //}
        //else if (strcmp(command, "vertex") == 0) { // if the command is a vertex
        //    float x, y, z;

        //    sscanf(line, "vertex %f %f %f", &x, &y, &z);

        //    if (scene.vertices.capacity() == scene.max_vertices)
        //        scene.vertices.push_back(Vec3(x, y, z));
        //    else {
        //        fprintf(stderr, "max_vertices not specified\n");
        //        exit(-1);
        //    }
        //}
        //else if (strcmp(command, "normal") == 0) { // If the command is a normal
        //    float x, y, z;

        //    sscanf(line, "normal %f %f %f", &x, &y, &z);

        //    if (scene.normals.capacity() == scene.max_normals)
        //        scene.normals.push_back(Vec3(x, y, z).Normalize());
        //    else {
        //        fprintf(stderr, "max_normals not specified\n");
        //        exit(-1);
        //    }
        //}
        else if (strcmp(command, "background") == 0) { // If the command is a background command
            float r, g, b;
            sscanf(line, "background %f %f %f", &r, &g, &b);

            scene.background = Vec3(r, g, b);
        }
        //else if (strcmp(command, "material") == 0) { // If the command is a material
        //    float ar, ag, ab; // ambient coefficients
        //    float dr, dg, db; // diffuse coefficients
        //    float sr, sg, sb, ns; // specular coefficients
        //    float tr, tg, tb, ior; // transmissiveness and index of refraction

        //    sscanf(line, "material %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n",
        //        &ar, &ag, &ab, &dr, &dg, &db, &sr, &sg, &sb, &ns, &tr, &tg, &tb, &ior);

        //    currMaterial = Material(Vec3(ar, ag, ab), Vec3(dr, dg, db), Vec3(sr, sg, sb), ns, Vec3(tr, tg, tb), ior);
        //    scene.materials.push_back(currMaterial);
        //}
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

static Map MapParse(Map& map, std::string fileName) {
    FILE *fp;
    char line[1024]; //Assumes no line is longer than 1024 characters!

    // open the file containing the scene description
    fp = fopen(fileName.c_str(), "r");

    // check for errors in opening the file
    if (fp == NULL) {
        fprintf(stderr, "Can't open file '%s'\n", fileName.c_str());
    }

    int i = 0;
    //Loop through reading each line
    while (fgets(line, 1024, fp)) { //Assumes no line is longer than 1024 characters!
        if (line[0] == '#') {
            //fprintf(stderr, "Skipping comment: %s", line);
            continue;
        }

        int fieldsRead; char row[100];

        // Bounds of grid
        int width, height;
        if ((fieldsRead = sscanf(line, "%d %d", &width, &height)) == 2) {
            map.Setup(width, height);
        }
        // Grid entries
        else if ((fieldsRead = sscanf(line, "%s", row)) == 1) {
            for (int j = 0; j < width; j++) {
                switch (row[i]) {
                case '0' :
                    map.layout[map.index(i, j)] = empty;
                    break;
                case 'W' :
                    map.layout[map.index(i, j)] = wall;
                    break;
                case 'S' :
                    map.layout[map.index(i, j)] = start;
                    break;
                case 'G' :
                    map.layout[map.index(i, j)] = goal;
                    break;
                case 'A' :
                    map.layout[map.index(i, j)] = door1;
                    break;
                case 'B' :
                    map.layout[map.index(i, j)] = door2;
                    break;
                case 'C' :
                    map.layout[map.index(i, j)] = door3;
                    break;
                case 'D' :
                    map.layout[map.index(i, j)] = door4;
                    break;
                case 'E' :
                    map.layout[map.index(i, j)] = door5;
                    break;
                case 'a' :
                    map.layout[map.index(i, j)] = key1;
                    break;
                case 'b' :
                    map.layout[map.index(i, j)] = key2;
                    break;
                case 'c' :
                    map.layout[map.index(i, j)] = key3;
                    break;
                case 'd' :
                    map.layout[map.index(i, j)] = key4;
                    break;
                case 'e' :
                    map.layout[map.index(i, j)] = key5;
                    break;
                default:
                    break;
                }
            }
            i++;
        }
        else { continue; }

    }

    return map;
}

#endif