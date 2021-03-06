#ifndef DRAWATTACK_SERVERLIST_HPP
#define DRAWATTACK_SERVERLIST_HPP

#include <vector>
#include <cpp3ds/Graphics.hpp>
#include <cpp3ds/Network.hpp>
#include <TweenEngine/TweenManager.h>
#include "ServerListItem.hpp"

#define SERVER_LIST_HOST "http://cruels.net"
#define SERVER_LIST_URI  "/drawattack.txt"

#define SERVER_LIST_FILE "servers.txt"

namespace DrawAttack {

class ServerList: public cpp3ds::Drawable {
public:
	ServerList();
	void reload();
	void deselect();
	void ping(cpp3ds::Time timeout);
	void addServer(const char* ip, unsigned short port);
	bool processEvent(const cpp3ds::Event& event);
	void update(float delta);
	ServerListItem* getSelectedItem();
	bool isLoading() const;

protected:
	void draw(cpp3ds::RenderTarget& target, cpp3ds::RenderStates states) const;

private:
	std::vector<std::unique_ptr<ServerListItem>> m_servers;
	TweenEngine::TweenManager   m_tweenManager;
	ServerListItem*             m_selected;
};

} // namespace DrawAttack

#endif // DRAWATTACK_SERVERLIST_HPP
