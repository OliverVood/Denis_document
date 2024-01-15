<?php

	namespace Base\Helper;

	use Base\Action;
	use Base\Templates\Buffering;

	class Pages {
		private Action $act;

		private int $current;
		private int $count;

		private string $name;

		public function __construct(Action $act, int $current, int $count, string $name = 'page') {
			$this->act = $act;

			$this->current = $current;
			$this->count = $count;

			$this->name = $name;
		}

		public function ToString(): string {
			Buffering::Start();
			if ($this->count > 1) {
				echo '<div class = "pagination">';
				if ($this->current > 1) {
					echo $this->GetFirst(1);
					echo $this->GetPrevious($this->current - 1);
				}
				echo $this->GetCurrent($this->current);
				if ($this->current < $this->count) {
					echo $this->GetNext($this->current + 1);
					echo $this->GetLast($this->count);
				}
				echo '</div>';
			}
			return Buffering::Read();
		}

		private function GetCurrent(int $number): string {
			return "<a class = 'current'>$number</a>";
		}

		private function GetPrevious(int $number): string {
			return $this->GetLink($number, '‹', 'previous');
		}

		private function GetNext(int $number): string {
			return $this->GetLink($number, '›', 'next');
		}

		private function GetFirst(int $number): string {
			return $this->GetLink($number, '«', 'first');
		}

		private function GetLast(int $number): string {
			return $this->GetLink($number, '»', 'last');
		}

		private function GetLink(int $number, string $content, string $class = ''): string {
			return $this->act->GetLinkHref($content, [$this->name => $number], ['class' => $class]);
		}

	}