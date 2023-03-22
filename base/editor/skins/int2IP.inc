<?php

	namespace Base\Editor\Skins;

	class Int2IP extends Skin {

		public function __construct(string $name) {
			parent::__construct($name);
		}

		public function ToVar(string $value) : string {
			return long2ip((int)$value);
		}

	}