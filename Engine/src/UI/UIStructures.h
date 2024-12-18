#pragma once
#include <SDL.h>
#include <imgui.h>
#include <vector>
#include <string>

// enum for each type of UI element, e.g. buttons, labels
enum UIElement { button = 0, label = 1, radioButton = 2 };

// struct for making buttons, labels, and any further feature
struct UIQueueData {
    int uniqueID;
    int groupID;
    UIElement elementType;
    bool enabled = true;
    ImVec2 pos;
    ImVec2 size;
    std::string text = "";

    UIQueueData(UIElement eType, ImVec2 p, ImVec2 s, const char* t, int uID, int gID) : elementType(eType), pos(p), size(s), text(t), uniqueID(uID), groupID(gID) {} //default constructor
    UIQueueData(UIElement eType, std::string t, ImVec2 p, int uID, int gID) : elementType(eType), text(t), pos(p), uniqueID(uID), groupID(gID) {} //constructor for label
    UIQueueData(UIElement eType, std::string t, ImVec2 p, ImVec2 s, int uID, int gID) : elementType(eType), text(t), pos(p), size(s), uniqueID(uID), groupID(gID) {} //constructor for button
};

struct Group {
    int groupID;
    ImVec2 pos;
    std::vector<UIQueueData> elementGroup;

    // Constructor
    Group(int ID, ImVec2 p, std::vector<UIQueueData> group) : groupID(ID), pos(p), elementGroup(group) {}
    Group(int ID) : groupID(ID) {};
};