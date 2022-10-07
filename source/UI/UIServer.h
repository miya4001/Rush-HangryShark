/*****************************************************************//**
 * @file   UIServer.h
 * @brief  UI���Ǘ�����T�[�o�N���X
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#pragma once
#include <appframe.h>

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  UI
   */
  namespace UI {
    class UIBase;
    /**
     * @class  UIServer
     * @brief  UI���Ǘ�����T�[�o�N���X
     */
    class UIServer {
    public:
      /**
       * @brief  �R���X�g���N�^
       */
      UIServer();
      /**
       * @brief  �f�X�g���N�^
       */
      ~UIServer();
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
       * @brief  UI��o�^
       * @param  ui UI�̃X�}�[�g�|�C���^
       */
      void RegisterUI(std::shared_ptr<UIBase> ui);

    private:
      //!< UI���W�X�g��
      std::vector<std::shared_ptr<UIBase>> _uiRegistry;
    };
  } // namespace UI
} // namespace Game