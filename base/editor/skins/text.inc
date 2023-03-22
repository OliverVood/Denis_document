<?php

	namespace Base\Editor\Skins;

	class Text extends Skin {

		public function __construct(string $name) {
			parent::__construct($name);
		}

		public function ToVar(string $value) : string {
			return $value;
		}

	}