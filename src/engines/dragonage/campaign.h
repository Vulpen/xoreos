/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  The context holding a Dragon Age: Origins campaign.
 */

#ifndef ENGINES_DRAGONAGE_CAMPAIGN_H
#define ENGINES_DRAGONAGE_CAMPAIGN_H

#include <vector>
#include <map>

#include "src/common/ustring.h"

#include "src/aurora/locstring.h"
#include "src/aurora/types.h"

#include "src/events/types.h"

#include "src/engines/aurora/resources.h"

#include "src/engines/dragonage/objectcontainer.h"
#include "src/engines/dragonage/object.h"

namespace Engines {

namespace DragonAge {

class Game;
class Area;

class Campaign : public DragonAge::Object, public DragonAge::ObjectContainer {
public:
	/** Return the unique ID of this campaign. */
	const Common::UString &getUID() const;

	const Aurora::LocString &getName() const;
	const Aurora::LocString &getDescription() const;

	/** Return the UID of the campaign this campaign/content extends, if any. */
	const Common::UString &getExtendsUID() const;

	bool isEnabled() const; ///< Is this Campaign enabled?
	bool isBioWare() const; ///< Is this an original campaign by BioWare?
	bool needsAuth() const; ///< Does this campaign need authorization from BioWare?

	/** Return the RIM file containing this area. */
	const Common::UString &getAreaRIM(const Common::UString &area) const;

	const std::vector<Common::UString> &getAreas() const;

	/** Move the player character to this area. */
	void movePC(const Common::UString &area);
	/** Move the player character to this position within the current area. */
	void movePC(float x, float y, float z);
	/** Move the player character to this position within this area. */
	void movePC(const Common::UString &area, float x, float y, float z);


private:
	/** A node in the RIM tree. */
	struct RIMNode {
		typedef std::vector<const RIMNode *> Children;

		Common::UString tag;  ///< Name of the node itself, not unique.
		Common::UString area; ///< ResRef of the area this node describes, if any.

		Common::UString environment; ///< Directory in which to find environment resources.
		Common::UString rim;         ///< The module RIM file.

		const RIMNode *parent;
		Children children;

		RIMNode(const RIMNode *p = 0);
		~RIMNode();
	};
	/** Map of area RIMNodes indexed by the area resref. */
	typedef std::map<Common::UString, const RIMNode *> AreaMap;


	Game *_game;

	Common::UString _uid;

	Common::UString _cifPath;
	Common::UString _addinBase;

	Aurora::LocString _name;
	Aurora::LocString _description;

	Common::UString _extends;

	bool _enabled;
	bool _bioware;
	bool _needsAuth;

	uint32 _priority;
	uint32 _format;
	uint32 _state;

	Common::UString _entryArea;
	Common::UString _entryAreaList;
	Common::UString _entryScript;
	Common::UString _entryClientScript;

	float _entryPosition[3];
	float _entryOrientation[3];

	std::vector<Common::UString> _packages;

	RIMNode *_rimRoot;
	AreaMap  _areaMap;

	std::vector<Common::UString> _areas;

	ChangeList _resources;
	ChangeList _tlks;

	Area *_area;
	Common::UString _newArea;

	std::list<Events::Event> _eventQueue;


	Campaign(Game &game, const Common::UString &cifPath = "",
	         const Common::UString &manifestPath = "", const Common::UString &addinBase = "");
	~Campaign();

	// .--- Loader
	void read(const Common::UString &cifPath, const Common::UString &manifestPath);
	void readCIFStatic(const Common::UString &path);
	RIMNode *readRIMs(const Aurora::GFF4Struct &node, const RIMNode *parent = 0);
	void readManifest(const Common::UString &path);

	void addAreaName(const RIMNode &node);

	void readCIFDynamic(const Common::UString &path);
	void loadResources();
	// '---

	// .--- Methods called by the Campaigns context
	/** Load the campaign for playing. */
	void load();
	/** Unload the campaign after playing. */
	void unload();

	/** Enter the campaign, starting it. */
	void enter();
	/** Leave the campaign, ending it. */
	void leave();

	/** Add a single event for consideration into the area event queue. */
	void addEvent(const Events::Event &event);
	/** Process the current event queue. */
	void processEventQueue();

	void loadArea();
	void unloadArea();
	bool changeArea();

	void enterArea(bool startArea = false);
	// '---

	friend class Campaigns;
};

} // End of namespace DragonAge

} // End of namespace Engines

#endif // ENGINES_DRAGONAGE_CAMPAIGN_H
