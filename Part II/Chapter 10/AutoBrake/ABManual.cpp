#include <iostream>
#include <stdexcept>
#include <functional>
using namespace std;

struct SpeedUpdate {
	double velocity;
};

struct CarDetected {
	double distance, velocity;
};

struct BrakeCommand {
	double time_to_collision;
};

struct ServiceBus {
	void publish(const BrakeCommand&);
};

using SpeedUpdateCallback = function<void (const SpeedUpdate&)>;
using CarDetectedCallback = function<void (const CarDetected&)>;

// Service bus interface
struct IServiceBus {
	virtual ~IServiceBus() = default;
	virtual void publish(const BrakeCommand&) = 0;
	virtual void subscribe(SpeedUpdateCallback) = 0;
	virtual void subscribe(CarDetectedCallback) = 0;
};

// Mock service bus
struct MockServiceBus : IServiceBus {
	BrakeCommand last_command{};
	int commands_published{};
	SpeedUpdateCallback speed_update_callback{};
	CarDetectedCallback car_detected_callback{};

	void publish(const BrakeCommand& cmd) override {
		commands_published++;
		last_command = cmd;
	}
	void subscribe(SpeedUpdateCallback callback) override {
		speed_update_callback = callback;
	}
	void subscribe(CarDetectedCallback callback) override {
		car_detected_callback = callback;
	}
};

class AutoBrake {
	double collision_threshold;
	double speed;

public:
	AutoBrake(IServiceBus& bus) : speed{}, collision_threshold{ 5 } {
		bus.subscribe([this](const SpeedUpdate& update) { speed = update.velocity; });
		bus.subscribe([this, &bus](const CarDetected& cd) {
			const auto relative_velocity = speed - cd.velocity;
			const auto time_to_collision = cd.distance / relative_velocity;
			if (time_to_collision > 0 && time_to_collision <= collision_threshold) {
				bus.publish(BrakeCommand{ time_to_collision });
			}
		});
	}

	void set_collision_threshold(double x) {
		if (x < 1) throw invalid_argument{ "Collision less than 1." };
		collision_threshold = x;
	}

	double get_collision_threshold() const {
		return collision_threshold;
	}

	double get_speed() const {
		return speed;
	}
};

constexpr void assert_that(bool statement, const char* message) {
	if (!statement) throw runtime_error{ message };
}

void initial_speed_zero() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	assert_that(auto_brake.get_speed() == 0L, "speed not equal to 0");
}

void collision_threshold_five() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	assert_that(auto_brake.get_collision_threshold() == 5L, "sensitivity is not 5");
}

void sensitivity_gt_1() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	try {
		auto_brake.set_collision_threshold(0.5L);
	} catch (const exception&) {
		return;
	}
	assert_that(false, "no exception thrown");
}

void run_test(void(*unit_test)(), const char* name) {
	try {
		unit_test();
		cout << "[+] Test " << name << " successful.\n";
	} catch (const exception& e) {
		cout << "[-] Test failure in " << name << ". " << e.what() << ".\n";
	}
}

void speed_saved() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	
	bus.speed_update_callback(SpeedUpdate{ 100L });
	assert_that(100L == auto_brake.get_speed(), "speed not saved to 100");
}

void no_alert_not_imminent() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };
	auto_brake.set_collision_threshold(2L);
	bus.speed_update_callback(SpeedUpdate{ 100L });
	bus.car_detected_callback(CarDetected{ 1000L, 50L });

	assert_that(bus.commands_published == 0, "brake command published");
}

void alert_when_imminent() {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };

	auto_brake.set_collision_threshold(10L);
	bus.speed_update_callback(SpeedUpdate{ 100L });
	bus.car_detected_callback(CarDetected{ 100L, 0L });
	assert_that(bus.commands_published == 1, "brake commands published not one");
	assert_that(bus.last_command.time_to_collision == 1L, "time to collision not computed correctly");
}

int main() {
	run_test(initial_speed_zero, "initial speed is 0");
	run_test(collision_threshold_five, "collision threshold is five");
	run_test(sensitivity_gt_1, "threshold is greater than one");
	run_test(speed_saved, "speed is saved");
	run_test(no_alert_not_imminent, "no alerts when no crash imminent");
	run_test(alert_when_imminent, "alerts when imminent");
}