#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>

struct FriendGroup
{
    std::set<int> friends;
    std::weak_ptr<FriendGroup> enemies;
};

void fuseGroups(std::vector<std::shared_ptr<FriendGroup>>& people, std::shared_ptr<FriendGroup> intoGroup, std::shared_ptr<FriendGroup> fromGroup) {
    for (int fid : fromGroup->friends) {
        intoGroup->friends.insert(fid);
        people[fid] = intoGroup;
    }
}

int main() {
#ifndef __LOCAL
    std::istream& input = std::cin;
    std::ostream& output = std::cout;
#else
    std::ifstream inTest("tests/war.in");
    std::istream& input = inTest;
    std::ostream& output = std::cout;
#endif

    size_t nPeople;
    input >> nPeople;

    std::vector<std::shared_ptr<FriendGroup>> friendGroupOf(nPeople);

    for (int i = 0; i < nPeople; ++i) {
        friendGroupOf[i] = std::shared_ptr<FriendGroup>(new FriendGroup());
        friendGroupOf[i]->friends.insert(i);
    }

    int code, x, y;
    do {
        input >> code >> x >> y;

        auto friendsX = friendGroupOf[x];
        auto friendsY = friendGroupOf[y];
        auto enemiesX = friendGroupOf[x]->enemies.lock();
        auto enemiesY = friendGroupOf[y]->enemies.lock();

        bool areFriends = friendsX->friends.count(y) > 0;
        bool areEnemies = enemiesX != nullptr && enemiesX->friends.count(y) > 0;

        switch (code) {
            case 1:
                if (areEnemies) {
                    output << -1 << '\n';
                    break;
                }

                if (areFriends) {
                    break;
                }

                // friends of my friend become my friends
                fuseGroups(friendGroupOf, friendsX, friendsY);

                if (enemiesX != nullptr && enemiesY != nullptr) {
                    // my friend's enemies become friends of my enemies
                    if (enemiesX != enemiesY) {
                        fuseGroups(friendGroupOf, enemiesX, enemiesY);
                    }

                    // my friend's enemies become my enemies
                    friendsX->enemies = enemiesX;
                    enemiesX->enemies = friendsX;
                }
                else if (enemiesX == nullptr && enemiesY != nullptr) {
                    // my friend's enemies become my enemies
                    friendsX->enemies = enemiesY;
                    enemiesY->enemies = friendsX;
                }
                break;

            case 2:
                if (areFriends) {
                    output << -1 << '\n';
                    break;
                }

                if (areEnemies) {
                    break;
                }

                if (enemiesX != nullptr) {
                    // enemies of my enemy become my friends
                    fuseGroups(friendGroupOf, friendsY, enemiesX);
                }
                if (enemiesY != nullptr) {
                    // enemies of my enemy become my friends
                    fuseGroups(friendGroupOf, friendsX, enemiesY);
                }
                friendsX->enemies = friendsY;
                friendsY->enemies = friendsX;
                break;

            case 3:
                output << (areFriends ? 1 : 0) << '\n';
                break;

            case 4:
                output << (areEnemies ? 1 : 0) << '\n';
                break;

            default:
                break;
        }
    } while(code != 0);

    output.flush();
    return 0;
}
