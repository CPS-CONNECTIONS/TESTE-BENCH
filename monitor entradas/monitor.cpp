#include <ctime>
#include <iostream>
#include <unistd.h>
#include <mraa/gpio.h>

string getTimestamp (){
    auto now = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(now);
    
    std::tm* local_time = std::localtime(&time_now);
    
    std::ostringstream oss;
    oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");

    return oss.str();
};

int main() {
    // Inicialização dos pinos
    mraa_gpio_context barramento0 = mraa_gpio_init(16);
    mraa_gpio_context barramento1 = mraa_gpio_init(18);
    mraa_gpio_context barramento2 = mraa_gpio_init_raw(71);
    mraa_gpio_context barramento3 = mraa_gpio_init_raw(57);

    if (!barramento0 || !barramento1 || !barramento2 || !barramento3) {
        std::cerr << "Erro ao inicializar os pinos GPIO." << std::endl;
        return 1;
    }

    mraa_gpio_dir(barramento0, MRAA_GPIO_IN);
    mraa_gpio_dir(barramento1, MRAA_GPIO_IN);
    mraa_gpio_dir(barramento2, MRAA_GPIO_IN);
    mraa_gpio_dir(barramento3, MRAA_GPIO_IN);

    while (true) {
        int valor0 = mraa_gpio_read(barramento0);
        int valor1 = mraa_gpio_read(barramento1);
        int valor2 = mraa_gpio_read(barramento2);
        int valor3 = mraa_gpio_read(barramento3);
        
        std::string timestamp = getTimestamp();

        std::cout << "CICLO  1: " << valor0 << " | "
                  << "PARADA 1: " << valor1 << " | "
                  << "CICLO  2: " << valor2 << " | "
                  << "PARADA 2: " << valor3 << " | " 
                  << "Timestamp: " << timestamp << std::endl;
        
        sleep(1);
    }

    mraa_gpio_close(barramento0);
    mraa_gpio_close(barramento1);
    mraa_gpio_close(barramento2);
    mraa_gpio_close(barramento3);
    
    return 0;
}
