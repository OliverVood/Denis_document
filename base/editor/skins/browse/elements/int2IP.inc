<?php

	namespace Base\Editor\Skins\Browse;

	use Base\Editor\Skins\SkinBrowse;

	class Int2IP extends SkinBrowse {

		public function __construct(string $title) {
			parent::__construct($title);
		}

		public function ToVar(mixed $value) : string {
			return long2ip((int)$value);
		}

	}