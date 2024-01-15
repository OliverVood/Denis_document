<?php

	namespace Base;

	abstract class Timestamp {
		static private array $timestamps	= [];
		static private int $current			= -1;
		static private int $last			= -1;

		static public function Start(string $name = ''): void {
			self::$timestamps[++self::$last] = ['name' => $name, 'start' => microtime(true), 'stop' => null, 'time' => null, 'parent' => self::$current];
			self::$current = self::$last;
		}

		static public function Stop(): void {
			if (self::$current == -1) return;
			self::$timestamps[self::$current]['stop'] = microtime(true);
			self::$timestamps[self::$current]['time'] = (int)(round(self::$timestamps[self::$current]['stop'] - self::$timestamps[self::$current]['start'], 6)  * 1000000);
			self::$current = self::$timestamps[self::$current]['parent'];
		}

		static public function GetTimestampList(): array {
			return self::$timestamps;
		}

	}