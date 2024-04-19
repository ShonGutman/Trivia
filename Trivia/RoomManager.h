#pragma once

#include "Room.h"
#include <map>

class RoomManager
{

public:

	/*
	* Function to get the singleton instance
	*
	* @return the instance of RoomManager
	*/
	static RoomManager& get();

	// Delete copy constructor and assignment operator to prevent copies
	RoomManager(const RoomManager& other) = delete;
	RoomManager& operator=(const RoomManager& other) = delete;


	/**
	 * Creates a new room and adds the author to it.
	 *
	 * @param auther The author of the room to be created.
	 * @param data The data of the room to be created.
	 * @throws std::runtime_error if a room with the same ID already exists.
	 */
	void createRoom(const LoggedUser auther, const RoomData data);

	/**
	 * Deletes a room with the specified ID.
	 *
	 * @param roomID The ID of the room to be deleted.
	 * @throws std::runtime_error if the room does not exist.
	 */
	void deleteRoom(const unsigned int roomID);

private:

	RoomManager() = default;

	std::map<unsigned int, Room> _rooms;
};
