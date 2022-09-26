/*****************************************************************//**
 * @file   SpawnEnemy.cpp
 * @brief  �G�̐������N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#include "SpawnEnemy.h"

namespace Game {
  namespace Spawn {
    SpawnEnemy::SpawnEnemy(const int number, const AppMath::Vector4 position, const AppMath::Vector4 rotation) {
      _number = number;
      _position = position;
      _rotation = rotation;
    }
  } // namespace Spawn
} // namespace Game