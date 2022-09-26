/*****************************************************************//**
 * @file   SpawnEnemy.h
 * @brief  �G�̐������N���X
 * 
 * @author �{�V�s��
 * @date   September 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  ����
   */
  namespace Spawn {
    namespace AppMath = AppFrame::Math;
    /**
     * @class SpawnEnemy
     * @brief �G�̐������N���X
     */
    class SpawnEnemy {
    public:
      /**
       * @brief  �R���X�g���N�^
       * @param  number ���ʔԍ�
       * @param  position �������W(�v���C���[���W�ւ̉���)
       * @param  rotation ��������
       */
      SpawnEnemy(const int number, const AppMath::Vector4 position, const AppMath::Vector4 rotation);
      /**
       * @brief  ���ʔԍ��̎擾
       * @return ���ʔԍ�
       */
      int GetNumber() {
        return _number;
      }
      /**
       * @brief  �������̎擾
       * @return �������W(�v���C���[���W�ւ̉���), ��������
       */
      std::pair<AppMath::Vector4, AppMath::Vector4> GetTransform() {
        return { _position, _rotation };
      }

    private:
      int _number{ -1 };  //!< ���ʔԍ�
      //!< �������W(�v���C���[���W�ւ̉���)
      AppMath::Vector4 _position;
      //!< ��������
      AppMath::Vector4 _rotation;
    };
  } // namespace Spawn
} // namespace Game