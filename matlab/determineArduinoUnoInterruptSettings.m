function [timer, compareMatchRegister, prescaler] = determineArduinoUnoInterruptSettings(interruptFrequency)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%function [compareMatchRegister, prescaler] = determineArduinoUnoInterruptSettings(interruptFrequency)
%
% Task: determine the interrupt settings for an Arduino Uno board given the desired interrupt frequency
%
% Input:
%	-interruptFrequency: the desiredinterrupt frequency (in Hz)
%
% Outputs:
% 	-compareMatchRegister: the value of the compare match register 
%					(must be less than 255 for timer0 and 2 and less than 65535 for timer1)
%	- prescaler: the value of the prescaler (possible choices: 1, 8, 64, 256, 1024)
%
%
% Guillaume Gibert
% 28/03/2021
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% config values
arduinoClockFrequency = 16000000; % 16 MHz
prescalerChoicesTimer0 = [1 8 64 256 1024];
prescalerChoicesTimer1 = [1 8 32 64 128 256 1024];

% output values
timer = [];
compareMatchRegister = [];
prescaler = [];

% for timer0 or 2 (8 bits)
maxCMRValue = 2^8;
fprintf("%%%%%%%%%%%%\n");
fprintf("Timer0 or Timer2 (8 bits):\n");
parsePrescalarChoices(prescalerChoicesTimer0);

% for timer1 (16 bits)
maxCMRValue = 2^16;
fprintf("%%%%%%%%%%%%\n");
fprintf("Timer1:\n");
parsePrescalarChoices(prescalerChoicesTimer1)
fprintf("%%%%%%%%%%%%\n");

	function parsePrescalarChoices(prescalerChoices) % nested function
		nbSolutions = 0;
		for l_prescaler=1:length(prescalerChoices)
			CMR = arduinoClockFrequency/(prescalerChoices(l_prescaler)*interruptFrequency)-1;
			if (CMR < maxCMRValue && mod(CMR,1) == 0)
				timer = [timer; 1];
				compareMatchRegister = [compareMatchRegister; CMR];
				prescaler = [prescaler; prescalerChoices(l_prescaler)];
				nbSolutions++;
				fprintf("CMR=%d, prescaler=%d\n", CMR, prescalerChoices(l_prescaler));
			end
		end
		if (nbSolutions == 0)
			fprintf("No solution\n");
		end
	end % nested function

end % end of main function
