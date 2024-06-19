#include "RoomManager.h"

static std::mutex _roomsMutex;
static std::mutex _questionNumMutex;

//init num of rooms joined to be zero at the start
int RoomManager::_amountOfRoomsEverJoined = 0;

RoomManager& RoomManager::get(IDatabase* database)
{
	static RoomManager instance(database);
	return instance;
}

RoomManager::RoomManager(IDatabase* database)
	:_database(database), _numberOfQuestions(database->getNumOfQuestions())
{
}

void RoomManager::createRoom(const LoggedUser& roomAdmin, const RoomData& data)
{

	if (data.numOfQuestionsInGame > _numberOfQuestions)
	{ 
		throw std::runtime_error("Questions limit in game is: " + std::to_string(_numberOfQuestions));
	}

	//create new room
	//lock the mutex - to protect _roomsMutex (shared var)
	std::unique_lock<std::mutex> locker(_roomsMutex);
	auto result = _rooms.insert({ data.id, Room(data, roomAdmin) });
	locker.unlock();

	//result is a pair of 2 values an iterator to object and bool to indicate if element was inserted successfully
	if (!result.second)
	{
		throw std::runtime_error("room with that ID already exists!");
	}

	RoomManager::_amountOfRoomsEverJoined++;
}

void RoomManager::deleteRoom(const unsigned int roomID)
{
	bool erased = false;

	{
		//lock the mutex - to protect _roomsMutex (shared var)
		std::lock_guard<std::mutex> locker(_roomsMutex);
		erased = _rooms.erase(roomID);
	}

	if (!erased)
	{
		throw std::runtime_error("room doesn't exist, can't erase ...");
	}
}

bool RoomManager::getRoomState(const unsigned int roomID) const
{
	return _rooms.at(roomID).getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms() const
{
	std::vector<RoomData> roomsData;

	for (auto& it : _rooms)
	{
		roomsData.push_back(it.second.getRoomData());
	}
	return roomsData;
}

Room& RoomManager::getRoom(const unsigned int roomID)
{
	return _rooms.at(roomID);
}

void RoomManager::removeUserFromAllRooms(const LoggedUser& user)
{
	std::vector<int> roomsToDelete;

	for (auto& pair : _rooms)
	{
		try
		{
			pair.second.removeUser(user);
		}

		catch (const std::exception&)
		{
			//if remove failed it means user isnt a member of room. no need to handle anything

			//check if user is the admi
			if (pair.second.getRoomAdmin() == user)
			{
				roomsToDelete.push_back(pair.first);
			}
		}

	}

	for (const auto& it : roomsToDelete)
	{
		//delete all rooms that relate to admin
		deleteRoom(it);
	}
}

const int RoomManager::getNextRoomId() const
{
	return RoomManager::_amountOfRoomsEverJoined + 1;
}

bool RoomManager::addQuestion(const std::string& question, const std::string& correct, const std::string incorecct[NUM_OF_INCORRECT])
{
	if (_database->addQuestion(question, correct, incorecct))
	{
		try
		{
			// lock the mutex to protect shared var
			std::unique_lock<std::mutex> locker(_questionNumMutex);
			// Change number of questions
			this->_numberOfQuestions++;
			locker.unlock();
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}