<?php

	namespace Base\Units;

	trait Objects {
		static protected ?self $object = null;

		public static function instance() : ?static { return static::$object; }
		public static function init() { if (!static::$object) new static(); }
	}