#ifndef FOLK_ENGINE__ENGINE_HPP
#define FOLK_ENGINE__ENGINE_HPP

#include <string>

namespace Folk {

    /// Functions that modify global engine state.
    class Engine {

    public:
        /// \brief \~spanish Emite una señal para salir de la aplicación.
        /// \brief \~english Signal the engine to exit (close the application).
        static void exit();

        /// \brief \~spanish Configura el título de la ventana.
        /// \brief \~english Set the title of the game window.
        static void setWindowTitle(const char *);

        /// \brief \~spanish Mostrar estadísticas de rendimiento en una ventana de ImGUI.
        /// \brief \~english Show performance statistics in an ImGUI dialog.
        static void setPerformanceMetricsEnabled(bool);

        /// \brief \~spanish Congigura el tiempo mínimo entre cuadros (i.e. el framerate maximo).
        /// \brief \~english Configure the minimum time between frames (i.e. maximum framerate).
        /**
         * \~spanish
         * \param time Tiempo mínimo, en segundos.
         *
         * \~english
         * \param time time in seconds.
        */
        static void setMinFrameTime(double time);

    }; // class Engine

}

#endif//FOLK__ENGINE_HPP