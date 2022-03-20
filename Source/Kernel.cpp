#include <HardwareCommunication/InterruptManager.h>

#include <Drivers/Keyboard.h>
#include <Drivers/Driver.h>
#include <Drivers/Mouse.h>

#include <Common/Console.h>
#include <Common/Types.h>

#include <GlobalDescriptorTable.h>
#include <Miscellaneous.h>

extern "C" constructor_t constructorsStart, constructorsEnd;

extern "C" void ConstructorsCall()
{
	for (constructor_t *i = &constructorsStart; i != &constructorsEnd; i++)
	{
		(*i)();
	}
}

extern "C" void KernelMain(uint32_t *multiBootHeader, uint32_t)
{
	GlobalDescriptorTable globalDescriptorTable;
	InterruptManager interruptManager(globalDescriptorTable);

	cout << "Initializing Hardware...\n";
	KeyboardDriver keyboardDriver(interruptManager);
	MouseDriver mouseDriver(interruptManager);

	cout << "Activating Hardware...\n\n";
	DriverManager driverManager;
	driverManager.Add(&keyboardDriver);
	driverManager.Add(&mouseDriver);
	driverManager.ActivateAll();

	interruptManager.Activate();

	SystemDateTime sdt = Miscellaneous::ReadRTCAndConvert();
	cout << "Time: " << (int64_t)sdt.time.hours << ":" << (int64_t)sdt.time.minutes << ":" << (int64_t)sdt.time.seconds << '\n';
	cout << "Date: " << (int64_t)sdt.date.months << "/" << (int64_t)sdt.date.days << "/" << (int64_t)sdt.date.years << "\n\n";
	cout << "Flexible@OS ~ $ ";
	Miscellaneous::SoundBeep();

	while (true)
	{
	}
}