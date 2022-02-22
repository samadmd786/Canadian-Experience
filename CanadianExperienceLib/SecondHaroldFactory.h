/**
 * @file SecondHaroldFactory.h
 * @author Md Samad
 *
 *
 */

#ifndef CANADIANEXPERIENCE_SECONDHAROLDFACTORY_H
#define CANADIANEXPERIENCE_SECONDHAROLDFACTORY_H

class Actor;

/**
 * A class to draw harold
 */
class SecondHaroldFactory {
private:

public:

    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};

#endif //CANADIANEXPERIENCE_SECONDHAROLDFACTORY_H
