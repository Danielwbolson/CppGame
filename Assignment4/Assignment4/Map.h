
#ifndef MAP_H_
#define MAP_H_

enum items {
    empty, wall, start, goal,
    door1, door2, door3, door4, door5, 
    key1, key2, key3, key4, key5
};

class Map {

private:
    int width, height;

public:
    items* layout;

    Map();
    int index(const int& i, const int& j) { return i * height + j; }
    void Setup(const int&, const int&);

};
#endif 