<?php

	namespace Base;

	trait Instance {
		static protected ?self $instance = null;

		public static function instance(): ?self { return self::$instance; }
		public static function init(): void { if (!self::$instance) self::$instance = new self(); }
	}