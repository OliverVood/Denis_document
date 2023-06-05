<?php

	namespace Base\Editor\Skins\Edit;

	class Hidden extends Input {

		public function __construct(string $title, string $name, string $default = '') {
			parent::__construct($title, $name, 'hidden', $default);
		}

	}