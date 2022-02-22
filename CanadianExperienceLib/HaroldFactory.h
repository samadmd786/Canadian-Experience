/**
 * @file HaroldFactory.h
 * @author Md Samad
 *
 *
 */

#ifndef CANADIANEXPERIENCE_HAROLDFACTORY_H
#define CANADIANEXPERIENCE_HAROLDFACTORY_H

#include "pch.h"
#include <memory>

/**
 * Factory class that builds the Harold character
 */

class Actor;

/**
 * A class to draw harold
 */
class HaroldFactory {
private:

public:

    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};

#endif //CANADIANEXPERIENCE_HAROLDFACTORY_H
