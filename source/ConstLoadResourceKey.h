/*****************************************************************//**
 * @file   ConstLoadResourceKey.h
 * @brief  ���\�[�X�ǂݍ��݃L�[�萔
 * 
 * @author �{�V�s��
 * @date   October 2022
 *********************************************************************/
#pragma once

/**
 * @brief  �Q�[��
 */
namespace Game {
  /**
   * @brief  �摜�n���h���L�[
   */
  namespace GraphicKey {
    constexpr auto UnderSea = "underSea";              //!< �C���摜
    constexpr auto AMG = "amg";                        //!< AMG�摜
    constexpr auto Title = "title";                    //!< �^�C�g���摜
    constexpr auto Start = "start";                    //!< �J�n�摜
    constexpr auto Quit = "quit";                      //!< �I���摜
    constexpr auto GameOver = "gameOver";              //!< �Q�[���I�[�o�[�摜
    constexpr auto Retry = "retry";                    //!< ���g���C�摜
    constexpr auto BackTitle = "backTitle";            //!< �^�C�g���o�b�N�摜
    constexpr auto Bubble = "bubble";                  //!< �A�摜
    constexpr auto HungryGauge = "hungryGauge";        //!< �󕠃Q�[�W�摜
    constexpr auto HungryGaugeBar = "hungryGaugeBar";  //!< �󕠃Q�[�W�o�[�摜
  } // namespace GraphicKey
  /**
   * @brief  ���f���n���h���L�[
   */
  namespace ModelKey {
    constexpr auto SeaSphere = "seaSphere";
    constexpr auto Shark = "shark";
    constexpr auto Shrimp = "shrimp";
    constexpr auto Tuna = "tuna";
    constexpr auto Jerryfish = "jerryfish";
  } // namespace ModelKey
  /**
   * @brief  �����n���h���L�[
   */
  namespace SoundKey {
    constexpr auto Bubble = "bubble";
    constexpr auto Hungry = "hungry";
  } // namespace SoundKey
}