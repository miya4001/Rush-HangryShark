/*****************************************************************//**
 * @file   ConstLoadResourceKey.h
 * @brief  リソース読み込みキー定数
 * 
 * @author 宮澤耀生
 * @date   October 2022
 *********************************************************************/
#pragma once

/**
 * @brief  ゲーム
 */
namespace Game {
  /**
   * @brief  画像ハンドルキー
   */
  namespace GraphicKey {
    constexpr auto UnderSea = "underSea";              //!< 海中画像
    constexpr auto AMG = "amg";                        //!< AMG画像
    constexpr auto Title = "title";                    //!< タイトル画像
    constexpr auto Start = "start";                    //!< 開始画像
    constexpr auto Explain = "explain";                //!< 説明画像
    constexpr auto Quit = "quit";                      //!< 終了画像
    constexpr auto Back = "back";                      //!< バック画像
    constexpr auto Explanation = "Explanation";        //!< ゲーム説明画像
    constexpr auto Pause = "pause";                    //!< ポーズ画像
    constexpr auto Continue = "continue";              //!< 続行画像
    constexpr auto Retire = "retire";                  //!< リタイア画像
    constexpr auto GameOver = "gameOver";              //!< ゲームオーバー画像
    constexpr auto Retry = "retry";                    //!< リトライ画像
    constexpr auto BackTitle = "backTitle";            //!< タイトルバック画像
    constexpr auto GameClear = "gameClear";            //!< ゲームクリア画像
    constexpr auto Shrimp = "shrimp";                  //!< エビ数画像
    constexpr auto Tuna = "tuna";                      //!< マグロ数画像
    constexpr auto Jerryfish = "jerryfish";            //!< クラゲ数画像
    constexpr auto Bubble = "bubble";                  //!< 泡画像
    constexpr auto HungryGauge = "hungryGauge";        //!< 空腹ゲージ画像
    constexpr auto HungryGaugeBar = "hungryGaugeBar";  //!< 空腹ゲージバー画像
    constexpr auto TimerColon = "timerColon";          //!< タイマーコロン画像
    constexpr auto Number = "number";                  //!< 数字画像
  } // namespace GraphicKey
  /**
   * @brief  モデルハンドルキー
   */
  namespace ModelKey {
    constexpr auto SeaSphere = "seaSphere";  //!< 海中背景モデル
    constexpr auto Shark = "shark";          //!< サメモデル
    constexpr auto Shrimp = "shrimp";        //!< エビモデル
    constexpr auto Tuna = "tuna";            //!< マグロモデル
    constexpr auto Jerryfish = "jerryfish";  //!< クラゲモデル
  } // namespace ModelKey
  /**
   * @brief  エフェクトハンドルキー
   */
  namespace EffectKey {
    constexpr auto Blood = "blood";          //!< 血エフェクト
    constexpr auto Discover = "discover";    //!< 発見エフェクト
    constexpr auto Paralysis = "paralysis";  //!< 麻痺エフェクト
  } // namespace EffectKey
  /**
   * @brief  エフェクト拡大率
   */
  namespace EffectMagni {
    constexpr float Blood = 5.0f;      //!< 血エフェクト拡大率
    constexpr float Discover = 20.0f;  //!< 発見エフェクト拡大率
    constexpr float Paralysis = 8.0f;  //!< 麻痺エフェクト拡大率
  } // namespace EffectMagni
  /**
   * @brief  音源ハンドルキー
   */
  namespace SoundKey {
    constexpr auto Bubble1 = "bubble1";      //!< 泡1SE
    constexpr auto Bubble2 = "bubble2";      //!< 泡2SE
    constexpr auto Hungry = "hungry";        //!< 空腹SE
    constexpr auto Bite = "bite";            //!< 噛みつきSE
    constexpr auto Eat = "eat";              //!< 捕食SE
    constexpr auto Paralysis = "paralysis";  //!< 麻痺SE
    constexpr auto Splash = "splash";        //!< しぶきSE
    constexpr auto Drawn = "drawn";          //!< 溺れるSE
    constexpr auto Whistle = "whistle";      //!< ホイッスルSE
  } // namespace SoundKey
}