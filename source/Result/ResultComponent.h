/*****************************************************************//**
 * @file   ResultComponent.h
 * @brief  ���U���g�R���|�[�l���g
 * 
 * @author �{�V�s��
 * @date   December 2022
 *********************************************************************/
#pragma once
#include "../Enemy/EnemyBase.h"

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  ���U���g
   */
  namespace Result {
    /**
     * @class  ResultComponent
     * @brief  ���U���g�R���|�[�l���g
     */
    class ResultComponent {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      ResultComponent();
      /**
       * @brief  �f�X�g���N�^
       */
      ~ResultComponent();
      /**
       * @brief  ���
       */
      void Release();
      /**
       * @brief  ���S���J�E���g
       * @param  enemy �G�̎��ʂ̗񋓌^
       */
      void DeadCount(Enemy::EnemyBase::EnemyID enemy);
      /**
       * @brief  �G�r���̎擾
       * @return �G�r��
       */
      int GetShrimp() {
        return _shrimp;
      }
      /**
       * @brief  �}�O�����̎擾
       * @return �}�O����
       */
      int GetTuna() {
        return _tuna;
      }
      /**
       * @brief  �N���Q���̎擾
       * @return �N���Q��
       */
      int GetJerryfish() {
        return _jerryfish;
      }

    private:
      int _shrimp{ 0 };     //!< �G�r��
      int _tuna{ 0 };       //!< �}�O����
      int _jerryfish{ 0 };  //!< �N���Q��
    };
  } // namespace Result
} // namespace Game