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
 *  Displaying the progress in loading a game.
 */

#ifndef ENGINES_AURORA_LOADPROGRESS_H
#define ENGINES_AURORA_LOADPROGRESS_H

#include "common/ustring.h"

namespace Graphics {
	namespace Aurora {
		class Text;
	}
}

namespace Engines {

class LoadProgress {
public:
	/** Create a load progress display.
	 *
	 *  steps specifies the number of steps that are gone through in
	 *  the process of loading the game. The very first step is the 0%
	 *  mark, the very last the 100% mark. Obviously, there needs to be
	 *  at least two steps.
	 *
	 *  An example with five steps:
	 *  - Step 0:   0%
	 *  - Step 1:  25%
	 *  - Step 2:  50%
	 *  - Step 3:  75%
	 *  - Step 4: 100%
	 */
	LoadProgress(uint steps);
	~LoadProgress();

	/** Take a step in advancing the progress. */
	void step(const Common::UString &description);

private:
	/** The length of the progress bar in characters. */
	static const int kBarLength = 50;

	uint _steps;       ///< The number of total steps.
	uint _currentStep; ///< The current step we're on.

	double _stepAmount;    ///< The amount to step each time.
	double _currentAmount; ///< The accumulated amount.

	/** The text containing the description of the current step. */
	Graphics::Aurora::Text *_description;

	// The progress bar, in three parts
	Graphics::Aurora::Text *_barUpper;    ///< The upper border of the progress bar.
	Graphics::Aurora::Text *_barLower;    ///< The lower border of the progress bar.
	Graphics::Aurora::Text *_progressbar; ///< The actual progress bar.

	/** The text containing the current percentage of done-ness. */
	Graphics::Aurora::Text *_percent;


	static Common::UString createProgressbar(uint length, double filled);
	static Common::UString createProgressbarUpper(uint length);
	static Common::UString createProgressbarLower(uint length);
};

} // End of namespace Engines

#endif // ENGINES_AURORA_LOADPROGRESS_H
