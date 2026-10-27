#include <Robot/IStamina.h>
#include <iostream>


int IStamina::get_stamina() const {
    return stamina;
}

int IStamina::get_max_stamina() const {
    return max_stamina;
}


void IStamina::set_stamina(int stamina) {
    if (stamina < 0) {
        std::cerr << "Введено неккоректное значение!" << std::endl;
        return;
    }
    this->stamina = std::min(max_stamina, stamina);
}

void IStamina::set_max_stamina(int max_stamina) {
    if (max_stamina <= 0) {
        std::cerr << "Введено неккоректное значение!" << std::endl;
        return;
    }
    stamina = std::min(max_stamina, stamina);
    this->max_stamina = max_stamina;
}

void IStamina::restore_stamina(int amount) {
	if (amount > 0)
		stamina += std::min(amount, max_stamina - stamina);
}

void IStamina::spend_stamina(int stamina) {
    this->stamina -= stamina;
}

bool IStamina::can_spend_stamina(int cost) const {
    return stamina >= cost;
}

bool IStamina::try_spend_stamina(int cost) {
    if (!can_spend_stamina(cost)) return false;
    stamina -= cost;
    return true;
}
