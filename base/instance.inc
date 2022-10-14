<?php

	namespace Base;

	trait Instance {
		static protected ?self $instance = null;

		public static function instance(): ?static { return static::$instance; }
		public static function init() { if (!static::$instance) self::$instance = new static(); }
	}