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
    constexpr auto Explain = "explain";                //!< �����摜
    constexpr auto Quit = "quit";                      //!< �I���摜
    constexpr auto Back = "back";                      //!< �o�b�N�摜
    constexpr auto Explanation = "Explanation";        //!< �Q�[�������摜
    constexpr auto Pause = "pause";                    //!< �|�[�Y�摜
    constexpr auto Continue = "continue";              //!< ���s�摜
    constexpr auto Retire = "retire";                  //!< ���^�C�A�摜
    constexpr auto GameOver = "gameOver";              //!< �Q�[���I�[�o�[�摜
    constexpr auto Retry = "retry";                    //!< ���g���C�摜
    constexpr auto BackTitle = "backTitle";            //!< �^�C�g���o�b�N�摜
    constexpr auto GameClear = "gameClear";            //!< �Q�[���N���A�摜
    constexpr auto Shrimp = "shrimp";                  //!< �G�r���摜
    constexpr auto Tuna = "tuna";                      //!< �}�O�����摜
    constexpr auto Jerryfish = "jerryfish";            //!< �N���Q���摜
    constexpr auto Bubble = "bubble";                  //!< �A�摜
    constexpr auto HungryGauge = "hungryGauge";        //!< �󕠃Q�[�W�摜
    constexpr auto HungryGaugeBar = "hungryGaugeBar";  //!< �󕠃Q�[�W�o�[�摜
    constexpr auto TimerColon = "timerColon";          //!< �^�C�}�[�R�����摜
    constexpr auto Number = "number";                  //!< �����摜
  } // namespace GraphicKey
  /**
   * @brief  ���f���n���h���L�[
   */
  namespace ModelKey {
    constexpr auto SeaSphere = "seaSphere";  //!< �C���w�i���f��
    constexpr auto Shark = "shark";          //!< �T�����f��
    constexpr auto Shrimp = "shrimp";        //!< �G�r���f��
    constexpr auto Tuna = "tuna";            //!< �}�O�����f��
    constexpr auto Jerryfish = "jerryfish";  //!< �N���Q���f��
  } // namespace ModelKey
  /**
   * @brief  �G�t�F�N�g�n���h���L�[
   */
  namespace EffectKey {
    constexpr auto Blood = "blood";          //!< ���G�t�F�N�g
    constexpr auto Discover = "discover";    //!< �����G�t�F�N�g
    constexpr auto Paralysis = "paralysis";  //!< ��ჃG�t�F�N�g
  } // namespace EffectKey
  /**
   * @brief  �G�t�F�N�g�g�嗦
   */
  namespace EffectMagni {
    constexpr float Blood = 5.0f;      //!< ���G�t�F�N�g�g�嗦
    constexpr float Discover = 20.0f;  //!< �����G�t�F�N�g�g�嗦
    constexpr float Paralysis = 8.0f;  //!< ��ჃG�t�F�N�g�g�嗦
  } // namespace EffectMagni
  /**
   * @brief  �����n���h���L�[
   */
  namespace SoundKey {
    constexpr auto Bubble1 = "bubble1";      //!< �A1SE
    constexpr auto Bubble2 = "bubble2";      //!< �A2SE
    constexpr auto Hungry = "hungry";        //!< ��SE
    constexpr auto Bite = "bite";            //!< ���݂�SE
    constexpr auto Eat = "eat";              //!< �ߐHSE
    constexpr auto Paralysis = "paralysis";  //!< ���SE
    constexpr auto Splash = "splash";        //!< ���Ԃ�SE
    constexpr auto Drawn = "drawn";          //!< �M���SE
    constexpr auto Whistle = "whistle";      //!< �z�C�b�X��SE
  } // namespace SoundKey
}