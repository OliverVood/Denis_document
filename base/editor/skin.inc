<?php

	namespace Base\Editor\Skins;

	abstract class Skin {
		protected string $name;

		public function __construct(string $name) {
			$this->name = $name;
		}

		abstract public function ToVar(string $value): string;

		public function GetName(): string { return $this->name; }

	}

	require DIR_BASE . 'editor/skins/text.inc';
	require DIR_BASE . 'editor/skins/int2IP.inc';