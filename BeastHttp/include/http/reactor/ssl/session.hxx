#if not defined BEASTHTTP_REACTOR_SSL_SESSION_HXX
#define BEASTHTTP_REACTOR_SSL_SESSION_HXX

#include <http/base/cb.hxx>
#include <http/base/request_processor.hxx>
#include <http/base/queue.hxx>
#include <http/base/timer.hxx>
#include <http/base/regex.hxx>
#include <http/base/strand_stream.hxx>
#include <http/base/lockable.hxx>

#include <http/common/ssl/connection.hxx>
#include <http/common/detect.hxx>

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/string_body.hpp>

#define BEASTHTTP_REACTOR_SSL_SESSION_TRY_INVOKE_FLESH_TYPE(router) \
    flesh_type(std::declval<boost::asio::ssl::context&>(), \
               std::declval<socket_type>(), \
               router.resource_map(), \
               router.method_map(), \
               router.regex_flags(), \
               &router.mutex(), \
               std::declval<buffer_type>(), \
               std::declval<_OnAction>()...)

#define BEASTHTTP_REACTOR_SSL_SESSION_TRY_INVOKE_FLESH_TYPE_LEGACY() \
    flesh_type(std::declval<boost::asio::ssl::context&>(), \
               std::declval<socket_type>(), \
               std::declval<std::shared_ptr<resource_map_type>>(), \
               std::declval<std::shared_ptr<method_map_type>>(), \
               std::declval<regex_flag_type>(), \
               std::declval<mutex_type*>(), \
               std::declval<buffer_type>(), \
               std::declval<_OnAction>()...)

namespace _0xdead4ead {
namespace http {
namespace reactor {
namespace ssl {

template</*Prototype request message*/
         class Body = boost::beast::http::string_body,
         class Fields = boost::beast::http::basic_fields<std::allocator<char>>,
         /*Message's buffer*/
         class Buffer = boost::beast::flat_buffer,
         /*Connection param's*/
         class Protocol = boost::asio::ip::tcp,
         class Socket = boost::asio::basic_stream_socket<Protocol>,
         /*Timer param's*/
         class Clock = boost::asio::chrono::steady_clock,
         template<typename, typename...> class Timer = boost::asio::basic_waitable_timer,
         /*Callback list container*/
         template<typename> class Entry = std::function,
         template<typename, typename...> class Container = std::vector,
         /*Resources container*/
         template<typename Key, typename Value, typename... Args> class MethodMap = std::map,
         template<typename Key, typename Value, typename... Args> class ResourceMap = std::unordered_map,
         /*On error handler*/
         template<typename> class OnError = std::function,
         /*On timer expired handler*/
         template<typename> class OnTimer = std::function,
         /*On handshake handler*/
         template<typename> class OnHandshake = std::function>
class session
{
    using self_type = session;

    enum class context_policy { shared, weak };

public:

    template<class, context_policy>
    class context;

    class flesh;

    using flesh_type = flesh;

    using context_type = context<flesh_type, context_policy::shared>;

    using weak_context = context<flesh_type, context_policy::weak>;

    using resource_regex_type = std::string;

    using resource_type = boost::beast::string_view;

    using method_type = boost::beast::http::verb;

    using mutex_type = base::lockable::mutex_type;

    using body_type = Body;

    using fields_type = Fields;

    using cbexecutor_type = base::cb::executor;

    using request_type = boost::beast::http::request<body_type, fields_type>;

    template<class _Body, class _Fields>
    using response_type = boost::beast::http::response<_Body, _Fields>;

    using queue_type = base::queue<flesh>;

    using buffer_type = Buffer;

    using connection_type = common::ssl::connection<Socket, base::strand_stream::asio_type>;

    using socket_type = typename connection_type::socket_type;

    using ssl_stream_type = typename connection_type::ssl_stream_type;

    using timer_type = base::timer<Clock, Timer, base::strand_stream::asio_type>;

    using duration_type = typename timer_type::duration_type;

    using time_point_type = typename timer_type::time_point;

    using clock_type = typename timer_type::clock_type;

    using regex_type = base::regex;

    using regex_flag_type = typename regex_type::flag_type;

    using on_error_type = OnError<void (boost::system::error_code, boost::string_view)>;

    using on_handshake_type = OnHandshake<void (context_type)>;

    using on_timer_type = OnTimer<void (context_type)>;

    using storage_type = base::cb::storage<self_type, Entry, Container>;

    using resource_map_type = ResourceMap<resource_regex_type, std::shared_ptr<storage_type>>;

    using method_map_type = MethodMap<method_type, resource_map_type>;

    using shutdown_type = typename socket_type::shutdown_type;

    static_assert (base::traits::TryInvoke<on_timer_type, void(context_type)>::value,
                   "Invalid OnTimer handler type!");

    static_assert (base::traits::TryInvoke<on_handshake_type, void(context_type)>::value,
                   "Invalid OnHandshake handler type!");

    static_assert (base::traits::TryInvoke<on_error_type, void(boost::system::error_code, boost::string_view)>::value,
                   "Invalid OnError handler type!");

    class flesh : private base::strand_stream, base::request_processor<self_type>,
            public std::enable_shared_from_this<flesh>
    {
        using base_type = base::request_processor<self_type>;

        friend queue_type;

    public:

        socket_type&
        asio_socket();

        ssl_stream_type&
        asio_ssl_stream();

        flesh&
        handshake();

        flesh&
        handshake(duration_type const);

        flesh&
        handshake(time_point_type const);

        flesh&
        recv();

        flesh&
        recv(duration_type const);

        flesh&
        recv(time_point_type const);

        template<class _Body, class _Fields>
        flesh&
        send(response_type<_Body, _Fields>&);

        template<class _Body, class _Fields>
        flesh&
        send(response_type<_Body, _Fields>&&);

        template<class _Body, class _Fields>
        flesh&
        send(response_type<_Body, _Fields>&, duration_type const);

        template<class _Body, class _Fields>
        flesh&
        send(response_type<_Body, _Fields>&&, duration_type const);

        template<class _Body, class _Fields>
        flesh&
        send(response_type<_Body, _Fields>&, time_point_type const);

        template<class _Body, class _Fields>
        flesh&
        send(response_type<_Body, _Fields>&&, time_point_type const);

        template<class _Body, class _Fields>
        flesh&
        push(response_type<_Body, _Fields>&);

        template<class _Body, class _Fields>
        flesh&
        push(response_type<_Body, _Fields>&&);

        flesh&
        wait();

        flesh&
        wait(duration_type const);

        flesh&
        wait(time_point_type const);

        flesh&
        timer_cancel();

        flesh&
        eof();

        flesh&
        eof(duration_type const);

        flesh&
        eof(time_point_type const);

        void
        force_eof();

        void
        force_cls();

        template<class _OnHandshake>
        explicit
        flesh(boost::asio::ssl::context&,
              socket_type&&,
              std::shared_ptr<resource_map_type> const&,
              std::shared_ptr<method_map_type> const&,
              regex_flag_type,
              mutex_type*,
              buffer_type&&,
              _OnHandshake&&,
              typename std::enable_if<
              base::traits::TryInvoke<_OnHandshake,
              void(context_type)>::value, int>::type = 0);

        template<class _OnHandshake, class _OnError>
        explicit
        flesh(boost::asio::ssl::context&,
              socket_type&&,
              std::shared_ptr<resource_map_type> const&,
              std::shared_ptr<method_map_type> const&,
              regex_flag_type,
              mutex_type*,
              buffer_type&&,
              _OnHandshake&&,
              _OnError&&,
              typename std::enable_if<
              base::traits::TryInvoke<_OnHandshake,
              void(context_type)>::value and
              base::traits::TryInvoke<_OnError,
              void(boost::system::error_code,
                   boost::string_view)>::value, int>::type = 0);

        template<class _OnHandshake, class _OnError, class _OnTimer>
        explicit
        flesh(boost::asio::ssl::context&,
              socket_type&&,
              std::shared_ptr<resource_map_type> const&,
              std::shared_ptr<method_map_type> const&,
              regex_flag_type,
              mutex_type*,
              buffer_type&&,
              _OnHandshake&&,
              _OnError&&,
              _OnTimer&&,
              typename std::enable_if<
              base::traits::TryInvoke<_OnHandshake,
              void(context_type)>::value and
              base::traits::TryInvoke<_OnError,
              void(boost::system::error_code,
                   boost::string_view)>::value and
              base::traits::TryInvoke<_OnTimer,
              void(context_type)>::value, int>::type = 0);

    private:

        void
        on_timer(boost::system::error_code);

        void
        on_handshake(boost::system::error_code, std::size_t);

        void
        on_shutdown(boost::system::error_code);

        void
        on_read(boost::system::error_code, std::size_t);

        void
        on_write(boost::system::error_code, std::size_t, bool);

        void
        do_handshake();

        void
        do_shutdown();

        template<class _Body, class _Fields>
        void
        do_write(response_type<_Body, _Fields>&);

        template<class _Body, class _Fields>
        void
        do_push(response_type<_Body, _Fields>&);

        void
        do_read();

        void
        do_eof();

        void
        do_force_eof();

        void
        do_force_cls();

        void
        do_launch_timer();

        void
        do_timeout();

        void
        do_process_request();

        socket_type&
        get_asio_socket();

        ssl_stream_type&
        get_asio_ssl_stream();

        void
        do_timer_cancel();

        bool eof_ = false;

        mutex_type* router_mutex_;

        timer_type timer_;

        connection_type connection_;

        on_handshake_type on_handshake_;
        on_error_type on_error_;
        on_timer_type on_timer_;

        request_type request_;
        buffer_type buffer_;
        queue_type queue_;

    }; // class flesh

    template<class Flesh, context_policy policy>
    class context
    {
        std::shared_ptr<Flesh> flesh_p_;

        bool
        isOk()
        {
            return flesh_p_.operator bool();
        }

    public:

        context(Flesh& flesh)
            : flesh_p_{flesh.shared_from_this()}
        {
        }

        static context<Flesh, context_policy::shared>
        save(context<Flesh, context_policy::shared> other, bool& is_ok)
        {
            is_ok = other.isOk();

            return other;
        }

        context<Flesh, context_policy::weak>
        weak()
        {
            return context<Flesh, context_policy::weak>(flesh_p_);
        }

        socket_type&
        asio_socket() const
        {
            return flesh_p_->asio_socket();
        }

        ssl_stream_type&
        asio_ssl_stream() const
        {
            return flesh_p_->asio_ssl_stream();
        }

        void
        recv() const
        {
            flesh_p_->recv();
        }

        void
        recv(duration_type const duration) const
        {
            flesh_p_->recv(duration);
        }

        void
        recv(time_point_type const time_point) const
        {
            flesh_p_->recv(time_point);
        }

        template<class _Body, class _Fields>
        void
        send(response_type<_Body, _Fields>& response) const
        {
            flesh_p_->send(response);
        }

        template<class _Body, class _Fields>
        void
        send(response_type<_Body, _Fields>&& response) const
        {
            flesh_p_->send(std::move(response));
        }

        template<class _Body, class _Fields>
        void
        send(response_type<_Body, _Fields>& response,
             duration_type const duration) const
        {
            flesh_p_->send(response, duration);
        }

        template<class _Body, class _Fields>
        void
        send(response_type<_Body, _Fields>&& response,
             duration_type const duration) const
        {
            flesh_p_->send(std::move(response), duration);
        }

        template<class _Body, class _Fields>
        void
        send(response_type<_Body, _Fields>& response,
             time_point_type const time_point) const
        {
            flesh_p_->send(response, time_point);
        }

        template<class _Body, class _Fields>
        void
        send(response_type<_Body, _Fields>&& response,
             time_point_type const time_point) const
        {
            flesh_p_->send(std::move(response), time_point);
        }

        template<class _Body, class _Fields>
        void
        push(response_type<_Body, _Fields>& response) const
        {
            flesh_p_->push(response);
        }

        template<class _Body, class _Fields>
        void
        push(response_type<_Body, _Fields>&& response) const
        {
            flesh_p_->push(std::move(response));
        }

        void
        wait() const
        {
            flesh_p_->wait();
        }

        void
        wait(duration_type const duration) const
        {
            flesh_p_->wait(duration);
        }

        void
        wait(time_point_type const time_point) const
        {
            flesh_p_->wait(time_point);
        }

        void
        timer_cancel() const
        {
            flesh_p_->timer_cancel();
        }

        void
        eof() const
        {
            flesh_p_->eof();
        }

        void
        eof(duration_type const duration) const
        {
            flesh_p_->eof(duration);
        }

        void
        eof(time_point_type const time_point) const
        {
            flesh_p_->eof(time_point);
        }

        void
        force_eof() const
        {
            flesh_p_->force_eof();
        }

        void
        force_cls() const
        {
            flesh_p_->force_cls();
        }

    }; // class context<Flesh, context_policy::shared>

    template<class Flesh>
    class context<Flesh, context_policy::weak>
    {
        std::weak_ptr<Flesh> flesh_p_;

    public:

        context(std::shared_ptr<Flesh> flesh_p)
            : flesh_p_{flesh_p}
        {
        }

        bool
        expired() const
        {
            return flesh_p_.expired();
        }

        context<Flesh, context_policy::shared>
        load() const
        {
            return context<Flesh, context_policy::shared>(flesh_p_.lock());
        }

    }; // class context<Flesh, context_policy::weak>

    template<class Router, class... _OnAction>
    static auto
    handshake(boost::asio::ssl::context&, socket_type&&, Router const&, buffer_type&&,
              _OnAction&&...) -> typename std::decay<decltype (
            BEASTHTTP_REACTOR_SSL_SESSION_TRY_INVOKE_FLESH_TYPE(std::declval<Router const&>()),
            std::declval<context_type>())>::type;

    template<class Router, class... _OnAction>
    static auto
    handshake(boost::asio::ssl::context&, socket_type&&, Router const&,
              _OnAction&&...) -> typename std::decay<decltype (
            BEASTHTTP_REACTOR_SSL_SESSION_TRY_INVOKE_FLESH_TYPE(std::declval<Router const&>()),
            std::declval<context_type>())>::type;

    template<class Router, class TimePointOrDuration, class... _OnAction>
    static auto
    handshake(boost::asio::ssl::context&, socket_type&&, Router const&,
              TimePointOrDuration const, buffer_type&&, _OnAction&&...) -> typename std::decay<decltype (
            BEASTHTTP_REACTOR_SSL_SESSION_TRY_INVOKE_FLESH_TYPE(
                std::declval<Router const&>()).handshake(std::declval<TimePointOrDuration>()),
            std::declval<context_type>())>::type;

    template<class Router, class TimePointOrDuration, class... _OnAction>
    static auto
    handshake(boost::asio::ssl::context&, socket_type&&, Router const&,
              TimePointOrDuration const, _OnAction&&...) -> typename std::decay<decltype (
            BEASTHTTP_REACTOR_SSL_SESSION_TRY_INVOKE_FLESH_TYPE(
                std::declval<Router const&>()).handshake(std::declval<TimePointOrDuration>()),
            std::declval<context_type>())>::type;

    template<class... _OnAction>
    static auto
    force_eof(boost::asio::ssl::context&, socket_type&&, _OnAction&&...) -> decltype (
            void(BEASTHTTP_REACTOR_SSL_SESSION_TRY_INVOKE_FLESH_TYPE_LEGACY()));

    template<class... _OnAction>
    static auto
    force_cls(boost::asio::ssl::context&, socket_type&&, _OnAction&&...) -> decltype (
            void(BEASTHTTP_REACTOR_SSL_SESSION_TRY_INVOKE_FLESH_TYPE_LEGACY()));

}; // class session

namespace _default {

using session_type = session<>;

} // namespace _default
} // namespace ssl
} // namespace reactor
} // namespace http
} // namespace _0xdead4ead

#include <http/reactor/ssl/impl/session.hxx>

#endif // not defined BEASTHTTP_REACTOR_SSL_SESSION_HXX
