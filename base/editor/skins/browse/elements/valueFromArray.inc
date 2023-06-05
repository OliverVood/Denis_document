<?php

	namespace Base\Editor\Skins\Browse;

	use Base\Editor\Skins\SkinBrowse;

	class ValueFromArray extends SkinBrowse {
		private array $array;

		public function __construct(string $title, array $array) {
			parent::__construct($title);

			$this->array = $array;
		}

		public function ToVar(mixed $value): string {
			return $this->array[$value] ?? '';
		}

	}