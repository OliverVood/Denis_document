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
			$path = $this->href;
			if ($path == 'default') {
				$path = REQUEST;
				if ($this->area !== 'null') {
					$path .= "/{$this->area}";
				}
				if ($this->part !== 'null') {
					$path .= "/{$this->part}";
				}
			}

			$href = ' href = "' . $path . '"';
			$onclick = ' onclick = "' . $this->click . '"';
			$target = (isset($params['target'])) ? ' target = "' . $params['target'] . '"' : '';

			return "<a{$href}{$onclick}{$target}>{$content}</a>";
		}

	}