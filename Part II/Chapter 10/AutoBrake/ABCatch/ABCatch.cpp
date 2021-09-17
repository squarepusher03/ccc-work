#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <functional>
#include <iostream>
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
	AutoBrake(IServiceBus& bus) : speed{}, collision_threshold { 5 } {
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

TEST_CASE("AutoBrake") {
	MockServiceBus bus{};
	AutoBrake auto_brake{ bus };

	SECTION("intial car speed is 0") {
		REQUIRE(auto_brake.get_speed() == 0);
	}

	SECTION("collision threshold is five") {
		REQUIRE(auto_brake.get_collision_threshold() == Approx(5L));
	}

	SECTION("throws when sensitivity less than one") {
		REQUIRE_THROWS(auto_brake.set_collision_threshold(0.5L));
	}

	SECTION("saves speed after update") {
		bus.speed_update_callback(SpeedUpdate{ 100L });
		REQUIRE(100L == auto_brake.get_speed());
		bus.speed_update_callback(SpeedUpdate{ 50L });
		REQUIRE(50L == auto_brake.get_speed());
		bus.speed_update_callback(SpeedUpdate{ 0L });
		REQUIRE(0L == auto_brake.get_speed());
	}

	SECTION("no alert when not imminent") {
		auto_brake.set_collision_threshold(2L);
		bus.speed_update_callback(SpeedUpdate{ 100L });
		bus.car_detected_callback(CarDetected{ 1000L, 50L });
		REQUIRE(bus.commands_published == 0);
	}

	SECTION("alert when imminent") {
		auto_brake.set_collision_threshold(10L);
		bus.speed_update_callback(SpeedUpdate{ 100L });
		bus.car_detected_callback(CarDetected{ 100L, 0L });
		REQUIRE(bus.commands_published == 1);
		REQUIRE(bus.last_command.time_to_collision == Approx(1));
	}
}