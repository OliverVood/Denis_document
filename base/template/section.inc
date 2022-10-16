<?php

	namespace Base\Templates;

	class Section {
		private array $content = [];

		public function __construct() {  }

		public function Push(string $content) {
			$this->content[] = $content;
		}

		public function Browse() {
			foreach ($this->content as $content) echo $content;
		}

	}