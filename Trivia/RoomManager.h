#pragma once

#include "Room.h"
#include <map>
#include <string>
#include <mutex>
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
	 * @param roomAdmin The author and admin of the room to be created.
	 * @param data The data of the room to be created.
	 * @throws std::runtime_error if a room with the same ID already exists.
	 */
	void createRoom(const LoggedUser& roomAdmin, const RoomData& data);

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
	 * Retrieves a reference to the vector containing the data of all rooms.
	 *
	 * @return A reference to the vector of RoomData objects representing the data of all rooms.
	 */
	std::vector<RoomData> getRooms() const;

	/**
	 * Retrieves a reference to the room with the specified ID.
	 *
	 * @param roomID The ID of the room to retrieve.
	 * @return A reference to the Room object corresponding to the specified ID.
	 * @throws std::out_of_range if the room with the specified ID does not exist.
	 */
	Room& getRoom(const unsigned int roomID);

	/*
	* removes the user from all rooms it is inside + if it owns one it also deletes that room
	* 
	* @param user - user to remove from all rooms
	*/
	void removeUserFromAllRooms(const LoggedUser& user);

	/*
	* Gets ID of the next room (in order to maintaine unique id)
	* 
	* @return: a number of the next room id to be added
	*/
	const int getNextRoomId() const;

private:

	RoomManager() = default;

	std::map<unsigned int, Room> _rooms;

	static int _amountOfRoomsEverJoined;
};
