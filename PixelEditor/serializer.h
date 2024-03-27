/**
 * This is the header for the serializer
 * @authors Egor Chesnokov and Aditya Mukerjee
 */
#ifndef SERIALIZER_H
#define SERIALIZER_H
#include <QString>

// Forward Declaration
class Sprite;

class Serializer
{
public:
	Serializer() = default;

    static void serialize(Sprite& sprite);
    static void  deserialize(QString filePath, Sprite& sprite);

};

#endif // SERIALIZER_H
