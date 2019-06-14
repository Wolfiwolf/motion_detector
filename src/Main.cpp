#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <thread>
#include <functional>

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "vendor/stb_image/stb_image.hpp"

#include "Picture.hpp"



bool draw_objects(std::vector<Object*>& objects, int pic_width, int pic_height, Vec2& position_buffer)
{
    std::vector<int> positions;
    positions.reserve(objects.size() * 2);

    std::sort(objects.begin(), objects.end(), [](Object* x, Object* y)
    {
        return x->get_weight() > y->get_weight();
    });

    bool is_good = objects.size() != 0;

    if(0)
    {
        for(int i = 0; i < 1; i++)
        {

            float x = ((float)objects[i]->get_pos().x / pic_width) * 150;
            float y = ((float)objects[i]->get_pos().y / pic_height) * 50;

            positions.push_back(150 - x);
            positions.push_back(y);


        }
    }
    else
    {
        for(Object* obj : objects)
        {
            float x = ((float)obj->get_pos().x / pic_width) * 150;
            float y = ((float)obj->get_pos().y / pic_height) * 50;

            positions.push_back(150 - x);
            positions.push_back(y);

        }
    }


    static auto is_pos = [&positions](int x, int y)
    {
        for(int i = 0; i < positions.size();)
        {
            if(positions[i] == x && positions[i+1] == y)
                return true;
            i += 2;
        }

        return false;
    };

    std::cout << "--------------\n";
    for(int i = 0; i < 50; i++)
    {
        std::cout << "|";
        for(int p = 0; p < 150; p++)
        {
            if(is_pos(p, i) && is_good)
            {
                std::cout << "X";
            }
            else
                std::cout << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "--------------\n";

    if(!is_good)
        return false;

    position_buffer.x = positions[0];
    position_buffer.y = positions[1];

    return true;
}

bool is_diffrent(const Object* obj_1, const Object* obj_2)
{
    const Color& color_1 = obj_1->get_color();
    const Color& color_2 = obj_2->get_color();

    if(abs(color_1.r - color_2.r) > 20)
        return true;

    if(abs(color_1.g - color_2.g) > 20)
        return true;

    if(abs(color_1.b - color_2.b) > 20)
        return true;

    return false;
}

Object* merge_objects(const std::vector<Object*> objs)
{
    if(objs.size() == 0)
        return nullptr;
    int sum_x = 0;
    int sum_y = 0;

    for(Object* obj : objs)
    {
        sum_x += obj->get_pos().x;
        sum_y += obj->get_pos().y;
    }

    return new Object(sum_x/objs.size(), sum_y/objs.size());
}

void get_changed_zones(const Picture& prev_pic, const Picture& current_pic, std::vector<Object*>& changed_objects)
{
    const std::vector<Object*>& prev_objs = prev_pic.get_objects();
    const std::vector<Object*>& current_objs = current_pic.get_objects();

    for(int i = 0; i < current_objs.size(); i++)
    {
        if(is_diffrent(current_objs[i], prev_objs[i]))
        {
            changed_objects.push_back(current_objs[i]);
        }
    }

}

void get_picture_paths(std::vector<std::string>& buffer)
{
    system("ls res > picture_paths.txt");

    std::ifstream in_file("picture_paths.txt");

    std::string filepath;
    while(std::getline(in_file, filepath))
    {
        buffer.push_back(filepath);
    }
    remove("picture_paths.txt");
}

void take_pictures(bool* running)
{
    while(*running)
    {
        system("streamer -t 100 -r 5 -o res/cam.$$.jpeg ");

    }
}

bool streamer_is_installed()
{
    system("streamer -o pic.jpeg");

    std::ifstream in_file("pic.jpeg");

    if(!in_file.is_open())
        return false;

    remove("pic.jpeg");

    return true;

}

int main()
{
    system("mkdir res");

    if(!streamer_is_installed())
    {
        std::cout << "\nInstall streamer to start!\n";
        return 0;
    }

    system("clear");
    std::cout << "Put your terminal into fullscreen!\n";
    std::cout << "Place the computer or camera on a stable surface and don't move it.\n";
    std::cout << "Make slow movements at first so you get the feel for it.\n";
    std::cout << "To end the program exit terminal.\n";
    std::cout << "HAVE FUN!\n";
    std::cout << "\nPRESS ENTER TO START DETECTION\n";
    std::cin.get();

    std::vector<std::string> filepaths;

    bool running = true;

    std::thread camera(take_pictures, &running);

    sleep(2);

    get_picture_paths(filepaths);
    Picture prev_picture("res/" + filepaths[0]);
    prev_picture.group_zones();

    while(running)
    {
        filepaths.clear();

        get_picture_paths(filepaths);

        for(const std::string& filepath : filepaths)
        {

            Picture picture("res/" + filepath);
            picture.group_zones();

            std::vector<Object*> changed_zones;
            get_changed_zones(prev_picture, picture, changed_zones);


            Vec2 position;
            system("clear");

            draw_objects(changed_zones, picture.get_width(), picture.get_height(), position);


            prev_picture = picture;
        }

        system("rm -rf res/*");

    }

    camera.join();



    return 0;
}
