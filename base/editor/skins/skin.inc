<?php

	namespace Base\Editor\Skins;

	abstract class Skin {
		protected string $title;

		public function __construct(string $title) {
			$this->title = $title;
		}

		public function GetTitle(): string { return $this->title; }

		abstract public function ToVar(mixed $value): string;

	}

	require DIR_BASE . 'editor/skins/browse/skinBrowse.inc';
	require DIR_BASE . 'editor/skins/edit/skinEdit.inc';