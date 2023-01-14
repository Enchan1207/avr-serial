//
// USARTインタフェース
//
#ifndef _USART_H_
#define _USART_H_

#include "usart_base.hpp"

// ターゲットが持つUSARTインタフェースに対応するクラスのみを定義したいので、
// レジスタ定義の有無からI/Fの存在チェックを行う
#define MCU_HAS_NO_USART

#if defined(UBRRH) || defined(UBRR0H)
#undef MCU_HAS_NO_USART
#define MCU_HAS_USART0

// エイリアス(名前が長いので)
#define Serial0 usart::USART0::shared()
#define Serial Serial0

namespace usart {

/**
 * @brief 非同期シリアル通信インタフェース #0
 */
class USART0 final : public BaseUSART {
   private:
    void setBaudRate(const uint64_t&) const override;
    void setSendability(bool) const override;
    bool getSendability() const override;
    void setReceivability(bool) const override;
    bool getReceivability() const override;
    void setSendBufferInterruption(bool) const override;
    void setReceiveInterruption(bool) const override;

    USART0();

   public:
    USART0(const USART0&) = delete;
    USART0& operator=(const USART0&) = delete;

    /**
     * @brief 共有インスタンスの取得
     *
     * @return USART0& USART0の共有インスタンス
     */
    static USART0& shared() {
        static USART0 usart0;
        return usart0;
    }
};

}  // namespace usart

#endif

#if defined(UBRR1H)
#ifdef MCU_HAS_NO_USART
#undef MCU_HAS_NO_USART
#endif
#define MCU_HAS_USART1

// エイリアス(名前が長いので)
#define Serial1 usart::USART1::shared()

namespace usart {

/**
 * @brief 非同期シリアル通信インタフェース #1
 */
class USART1 final : public BaseUSART {
   private:
    void setBaudRate(const uint64_t&) const override;
    void setSendability(bool) const override;
    bool getSendability() const override;
    void setReceivability(bool) const override;
    bool getReceivability() const override;
    void setSendBufferInterruption(bool) const override;
    void setReceiveInterruption(bool) const override;

    USART1();

   public:
    USART1(const USART1&) = delete;
    USART1& operator=(const USART1&) = delete;

    /**
     * @brief 共有インスタンスの取得
     *
     * @return USART1& USART1の共有インスタンス
     */
    static USART1& shared() {
        static USART1 usart1;
        return usart1;
    }
};

}  // namespace usart

#endif

#if defined(UBRR2H)
#ifdef MCU_HAS_NO_USART
#undef MCU_HAS_NO_USART
#endif
#define MCU_HAS_USART2

// エイリアス(名前が長いので)
#define Serial2 usart::USART2::shared()

namespace usart {

/**
 * @brief 非同期シリアル通信インタフェース #2
 */
class USART2 final : public BaseUSART {
   private:
    void setBaudRate(const uint64_t&) const override;
    void setSendability(bool) const override;
    bool getSendability() const override;
    void setReceivability(bool) const override;
    bool getReceivability() const override;
    void setSendBufferInterruption(bool) const override;
    void setReceiveInterruption(bool) const override;

    USART2();

   public:
    USART2(const USART2&) = delete;
    USART2& operator=(const USART2&) = delete;

    /**
     * @brief 共有インスタンスの取得
     *
     * @return USART2& USART2の共有インスタンス
     */
    static USART2& shared() {
        static USART2 usart2;
        return usart2;
    }
};

}  // namespace usart

#endif

#if defined(UBRR3H)
#ifdef MCU_HAS_NO_USART
#undef MCU_HAS_NO_USART
#endif
#define MCU_HAS_USART3

// エイリアス(名前が長いので)
#define Serial3 usart::USART3::shared()

namespace usart {

/**
 * @brief 非同期シリアル通信インタフェース #3
 */
class USART3 final : public BaseUSART {
   private:
    void setBaudRate(const uint64_t&) const override;
    void setSendability(bool) const override;
    bool getSendability() const override;
    void setReceivability(bool) const override;
    bool getReceivability() const override;
    void setSendBufferInterruption(bool) const override;
    void setReceiveInterruption(bool) const override;

    USART3();

   public:
    USART3(const USART3&) = delete;
    USART3& operator=(const USART3&) = delete;

    /**
     * @brief 共有インスタンスの取得
     *
     * @return USART3& USART3の共有インスタンス
     */
    static USART3& shared() {
        static USART3 usart3;
        return usart3;
    }
};

}  // namespace usart

#endif

// USART I/Fを持たない場合
#ifdef MCU_HAS_NO_USART
#warning "usart.h is included, but target MCU has no USART Interface."
#endif

#endif
