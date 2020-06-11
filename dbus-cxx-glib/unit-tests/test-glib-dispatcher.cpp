#include <dbus-cxx-glib.h>

#include "calleeclass.h"

static int doexit( gpointer user_data ){
    GMainLoop* loop = static_cast<GMainLoop*>( user_data );
    g_main_loop_quit( loop );
    return 0;
}

int main(int argc, char** argv){
    std::shared_ptr<DBus::Dispatcher> disp;
    GMainLoop* mainLoop;

    DBus::setLoggingFunction( DBus::logStdErr );
    DBus::setLogLevel( SL_TRACE );

    mainLoop = g_main_loop_new( nullptr, false );

    disp = DBus::GLib::GLibDispatcher::create();

    std::shared_ptr<DBus::Connection> conn = disp->create_connection( DBus::BusType::SESSION );
    conn->request_name( "dbuscxx.test" );
    std::shared_ptr<CalleeClass> callee = CalleeClass::create( "/test" );

    conn->register_object( callee, DBus::ThreadForCalling::CurrentThread );

    g_timeout_add( 1000, doexit, mainLoop );

    g_main_loop_run( mainLoop );

    g_main_loop_unref( mainLoop );

    return 0;
}
