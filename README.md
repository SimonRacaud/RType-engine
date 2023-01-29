This project aims to recreate the R-Type game and add a multiplayer mode to it. we had to implement a multi-threaded server using Boost::asio and a graphical client in SFML.

Compatible Windows and GNU/Linux.

# Project components

- Game client. Managing clients' connections. (/client)
- Game server (/server)
- Generic Game Engine using an Entity-Component-System (ECS) (/libs/GameEngine)
- A library to manage custom configuration files (/libs/ConfigFile) [Example](https://github.com/SimonRacaud/RType_Game-Engine/blob/4ca4eda1debe330835ba68a0b5d68fd879de1250/libs/ConfigFile/example/example.config)
- A library to define the game's enemies geenrically. Compiled as shared libraries and loaded dynamically. (/libs/Enemies)
- A generic interface for networking (/libs/Network)
- A generic interface for the GUI. Allows to easily change of graphical library without much code modifications. (/libs/Sfml)

# Preview

![Menu1](/github/menu1.png)
![Menu2](/github/menu2.png)
![Game](/github/game1.png)
![GameOver](/github/gameover.png)

# Usage

```
mkdir build && cd build && conan install .. --build=missing && cmake
.. -G “Unix Makefiles” && cmake --build .
```

# Server

- The server must be multi-threaded
- The server must be able to handle more than one game at a time
- The server must be able to handle multiple games in a row
- The server must be the referee of all games it manages.

# Client

- The client is the display terminal of the game.

- The client must contain anything necessary to display the game and handle player input.
- The client must use the SFML.

# Requirements

## Platforms

- The project must be OS independent. (Only Linux compliant at delivery)
- The project must be built using a CMake and dependencies must be handled using conan.

## Protocol

- You must design a binary protocol for client/server communications. (Cf rfc9999.txt)
- You must use UDP for communications between the server and the clients.
- A second connection using TCP can be tolerated but you must provide a strong justification.
- You must document your protocol and the documentation must be an RFC as discribed in RFC 2223.
- Your RFC must be formatted like an official RFC.
- You must write the RFC in ASCII format.
- You must respect standard RFC keywords as described in RFC 2119.

## Libraries

- You must use the SFML on the client side and any rendering must be done using the SFML.
- You are allowed to use Boost::ASIO for your server.

## Game Engine

The game engine is the core foundation of any video game: it determines how you represent an object in-game, how the coordinate system works, and how the various systems of your game (graphics, physics, network... ) communicate.

- Ability to add systems to a game through the form of dynamic libraries, scripts...
- Your engine must provides type-safety at compile-time.

