/*****************************************************************//**
 * @file   ObjectServer.h
 * @brief  �I�u�W�F�N�g���Ǘ�����T�[�o�N���X
 * 
 * @author �{�V�s��
 * @date   July 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  �v���C���[
   */
  namespace Player {
    class PlayerShark;
  }
  /**
   * @brief  �I�u�W�F�N�g
   */
  namespace Object {
    class ObjectBase;
    /**
     * @class ObjectServer
     * @brief �I�u�W�F�N�g���Ǘ�����T�[�o�N���X
     */
    class ObjectServer {
    public:
      /**
       * @brief �R���X�g���N�^
       */
      ObjectServer();
      /**
       * @brief �f�X�g���N�^
       */
      ~ObjectServer();
      /**
       * @brief  ���
       */
      void Release();
      /**
       * @brief  �X�V
       */
      void Process();
      /**
       * @brief  �`��
       */
      void Draw() const;
      /**
       * @brief  �I�u�W�F�N�g��o�^
       * @param  object �I�u�W�F�N�g�̃X�}�[�g�|�C���^
       * @param  add ���ڒǉ�(�f�t�H���g��false)
       */
      void RegisterObject(std::shared_ptr<ObjectBase> object, const bool add = false);
      /**
       * @brief  �I�u�W�F�N�g���W�X�g���̎擾
       * @return �I�u�W�F�N�g�̃V�F�A�[�h�|�C���^���i�[���ꂽ���I�z��
       */
      std::vector<std::shared_ptr<ObjectBase>> GetObjects() {
        return _objectRegistry;
      }
      /**
       * @brief  �v���C���[�̎擾
       * @return �v���C���[�̎Q��
       */
      std::shared_ptr<Player::PlayerShark> GetPlayerShark();

    private:
      /**
       * @brief  �I�u�W�F�N�g�̒ǉ�
       */
      void AddObjects();
      /**
       * @brief  �I�u�W�F�N�g���o�^����Ă��郌�W�X�g���̉��
       * @param  registry �I�u�W�F�N�g�̃V�F�A�[�h�|�C���^���i�[���ꂽ�R���e�i�̎Q��
       */
      void DeleteObjects(std::vector<std::shared_ptr<ObjectBase>>& registry);

      //!< �I�u�W�F�N�g���W�X�g��
      std::vector<std::shared_ptr<ObjectBase>> _objectRegistry;
      //!< �I�u�W�F�N�g�ǉ��\�񃌃W�X�g��
      std::vector<std::shared_ptr<ObjectBase>> _addObjectRegistry;
    };
  } // namespace Object
} // namespace Game