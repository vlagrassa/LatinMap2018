#ifndef SCREENMODE_H
#define SCREENMODE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

class ScreenMode {
public:
    ScreenMode() {};
    ScreenMode(const ScreenMode& orig) {
        for (ScreenMode* s : orig.references) {
            references.push_back(s);
        }
    };
    virtual ~ScreenMode() {};
    
    ScreenMode* run() {
        if (references.size() > 0) {
            return references.at(0);
        } else {
            return 0;
        }
    };
    
    void addReference(ScreenMode* s) {
        references.push_back(s);
    }
    std::vector<ScreenMode*> references;
private:
    
};

#endif /* SCREENMODE_H */
