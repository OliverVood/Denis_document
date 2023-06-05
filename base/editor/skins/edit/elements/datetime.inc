<?php

	namespace Base\Editor\Skins\Edit;

	class DateTime extends Input {

		public function __construct(string $title, string $name, string $default = '') {
			parent::__construct($title, $name, 'datetime-local', $default);
		}

	}