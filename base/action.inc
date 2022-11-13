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
		 * @param array $params - Параметры
		 * @return string
		 */
		public function GetLink(string $content, array $params = []): string {
			$href = ' href = "' . $this->href . '"';
			$onclick = ' onclick = "' . $this->click . '"';
			$target = (isset($params['target'])) ? ' target = "' . $params['target'] . '"' : '';

			return "<a{$href}{$onclick}{$target}>{$content}</a>";
		}

	}