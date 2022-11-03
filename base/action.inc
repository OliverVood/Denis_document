<?php

	namespace Base;

	Class Action {
		public string $area;
		public string $part;
		private string $href;
		private string $click;

		public function __construct(string $area = 'null', string $part = 'null', string $href = '', string $click = '') {
			$this->area 	= $area;
			$this->part 	= $part;
			$this->href 	= $href;
			$this->click 	= $click;
		}

		/**
		 * Возвращает ссылку
		 * @param string $content - Контент
		 * @return string
		 */
		public function GetLink(string $content): string {
			return '<a href = "' . $this->href . '" onclick = "' . $this->click . '">' . $content . '</a>';
		}

	}