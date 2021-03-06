#include "../header/entity.h"

Entity::Entity( Mesh *sides[ 6 ], Transform transform ) :
    sides{ sides[ 0 ], sides[ 1 ], sides[ 2 ], sides[ 3 ], sides[ 4 ], sides[ 5 ] }, transform( std::move( transform ) )
{
    for ( int i = 0; i < 6; ++i )
        this->sides[ i ]->transform.SetParent( &this->transform );
}

Entity::Entity( glm::vec3 mins, glm::vec3 maxs, Transform transform, Texture *texture ) :
    Entity( mins, maxs, std::move( transform ), new Texture *[ 6 ] { texture, texture, texture, texture, texture, texture } )
{
}
Entity::Entity( glm::vec3 mins, glm::vec3 maxs, Transform transform, Texture *textures[ 6 ] ) :
    sides{ 
        new Mesh( glm::vec2( mins.x, mins.y ), glm::vec2( maxs.x, maxs.y ), textures[ 0 ], Transform( glm::vec3( 0, 0, maxs.z ), glm::identity<glm::quat>(), glm::one<glm::vec3>() ) ),
        new Mesh( glm::vec2( mins.x, mins.y ), glm::vec2( maxs.x, maxs.y ), textures[ 1 ], Transform( glm::vec3( 0, 0, mins.z ), glm::identity<glm::quat>(), glm::one<glm::vec3>() ) ),
        new Mesh( glm::vec2( mins.z, mins.y ), glm::vec2( maxs.z, maxs.y ), textures[ 2 ], Transform( glm::vec3( mins.x, 0, 0 ), glm::angleAxis( M_PI_2f, glm::vec3( 0, 1, 0 ) ), glm::one<glm::vec3>() ) ),
        new Mesh( glm::vec2( mins.z, mins.y ), glm::vec2( maxs.z, maxs.y ), textures[ 3 ], Transform( glm::vec3( maxs.x, 0, 0 ), glm::angleAxis( M_PI_2f, glm::vec3( 0, 1, 0 ) ), glm::one<glm::vec3>() ) ),
        new Mesh( glm::vec2( mins.z, mins.x ), glm::vec2( maxs.z, maxs.x ), textures[ 4 ], Transform( glm::vec3( 0, maxs.y, 0 ), glm::angleAxis( M_PI_2f, glm::vec3( 1, 0, 0 ) ), glm::one<glm::vec3>() ) ),
        new Mesh( glm::vec2( mins.z, mins.x ), glm::vec2( maxs.z, maxs.x ), textures[ 5 ], Transform( glm::vec3( 0, mins.y, 0 ), glm::angleAxis( M_PI_2f, glm::vec3( 1, 0, 0 ) ), glm::one<glm::vec3>() ) ),
    }, transform( std::move( transform ) )
{
    for ( int i = 0; i < 6; ++i )
        this->sides[ i ]->transform.SetParent( &this->transform );
}

Entity::~Entity()
{
    for ( int i = 0; i < 6; ++i )
        delete sides[ i ];
}

void Entity::Render( Shader *shader )
{
    for ( int i = 0; i < 6; ++i )
        sides[ i ]->Render( shader );
}