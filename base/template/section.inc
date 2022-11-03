<?php

	namespace Base\Templates;

	class Section {
		private array $content = [];

		public function __construct() {  }

		public function Push(string $content): void {
			$this->content[] = $content;
		}

		public function Browse(): void {
			foreach ($this->content as $content) echo $content;
		}

	}