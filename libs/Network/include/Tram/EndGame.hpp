/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EndGame
*/

#ifndef ENDGAME_HPP_
#define ENDGAME_HPP_

#include "Tram/Serializable.hpp"

namespace Tram {
	class EndGame : public Tram::Serializable {
		public:
			EndGame();
			explicit EndGame(size_t roomId, bool win);

			size_t roomId{0};
			bool win = false;
			[[nodiscard]] uint8_t *serialize() const override;
			void deserialize(uint8_t *buffer) override;
			explicit EndGame(uint8_t *buffer);
			[[nodiscard]] size_t length() const override;
	};
}

#endif /* !ENDGAME_HPP_ */
