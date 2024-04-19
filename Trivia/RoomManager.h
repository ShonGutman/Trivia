#pragma once

#include "Room.h"
#include <map>
#include <vector>

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

	/**
	 * Retrieves the state of the room with the specified ID.
	 *
	 * @param roomID The ID of the room to retrieve the state for.
	 * @return true if the room is active, false otherwise.
	 * @throws std::out_of_range if the room with the specified ID does not exist.
	 */
	bool getRoomState(const unsigned int roomID) const;

	/**
	 * Retrieves a vector containing references to the data of all rooms.
	 *
	 * @return A vector of constant references to RoomData objects representing the data of all rooms.
	 */
	std::vector<const RoomData&> getRooms() const;

	/**
	 * Retrieves a constant reference to the room with the specified ID.
	 *
	 * @param roomID The ID of the room to retrieve.
	 * @return A constant reference to the Room object corresponding to the specified ID.
	 * @throws std::out_of_range if the room with the specified ID does not exist.
	 */
	const Room& getRoom(const unsigned int roomID) const;

private:

	RoomManager() = default;

	std::map<unsigned int, Room> _rooms;
};
