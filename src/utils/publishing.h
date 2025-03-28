/**
 * @file  publishing.h
 * @brief Implements the publish/subscribe pattern.
 *
 * Its a kind of signal and slot mechanism.
 *
 * @copyright Copyright(c) 2022 Peter Bestler
 */
#ifndef _SRC_UTILS_PUBLISHING
#define _SRC_UTILS_PUBLISHING

#include <vector>
#include <algorithm>

/**
 * If a class wants to receive TSubjects from a
 * publisher it have to implement this interface.
 *
 * The subscriber needs to be registered to a publisher
 * see @ref Publisher::addSubscriber
 */
template <typename TSubject>
class Subscriber
{
public:
	/**
	 * Callback for receiving a TSubject
	 */
	virtual void notify(const TSubject&) = 0;
	virtual ~Subscriber<TSubject>() {};
};

/**
 * If a class wants to distribute TSubject to different
 * subscriber it should derive from this class and
 * needs just to call publish with the TSubject.
 */
template <typename TSubject>
class Publisher
{
public:

	/**
	 * Constructor
	 */
	Publisher<TSubject>(): _subscribers() {}

	/**
	 * Destructor
	 */
	virtual ~Publisher<TSubject>() {};

	/**
	 * Adds a subscriber which is notified at calling publish.
	 * @param subscr The subscriber which wants to be notified.
	 */
	void addSubscriber(Subscriber<TSubject>& subscr)
	{
		_subscribers.emplace_back(&subscr);
	}

	/**
	 * Remove a subscriber which is notified at calling publish.
	 * @param subscr The subscriber which wants to be removed.
	 */
	void removeSubscriber(Subscriber<TSubject>& subscr)
	{
		_subscribers.erase(
				std::remove(_subscribers.begin(), _subscribers.end(), &subscr),
				_subscribers.end());
	}

	/**
	 * Distributes a TSubject to all registered subscribers.
	 */
	void publish(const TSubject& event)
	{
		for (auto subscr: _subscribers) {
			subscr->notify(event);
		}
	}

private:

	/** Registry of all subscribers which should be notified */
	std::vector<Subscriber<TSubject>*> _subscribers;
};

#endif /* _SRC_UTILS_PUBLISHING */
