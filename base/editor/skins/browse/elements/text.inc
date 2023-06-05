<?php

	namespace Base\Editor\Skins\Browse;

	use Base\Editor\Skins\SkinBrowse;

	class Text extends SkinBrowse {

		public function __construct(string $title) {
			parent::__construct($title);
		}

		public function ToVar(mixed $value): string {
			return nl2br(htmlspecialchars($value));
		}

	}