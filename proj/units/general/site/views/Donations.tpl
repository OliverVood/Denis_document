<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\Buffering;

	abstract class Donations {

		public static function ToVar(): string {
			Buffering::Start();
			self::Render();
			return Buffering::Read();
		}

		public static function Render(): void { ?>
			<div class = "view general donations">
				<div>
					<div class = "description">
						<div>Спасибо, что поддерживаете проект и цените вложенные усилия.</div>
						<div>Будьте внимательны при переводе. Не забудьте проверить номер карты и ФИО получателя.</div>
					</div>
					<div class = "card">
						<span class = "number">5</span>
						<span class = "number">4</span>
						<span class = "number">6</span>
						<span class = "number">9</span>
						<span>-</span>
						<span class = "number">6</span>
						<span class = "number">4</span>
						<span class = "number">0</span>
						<span class = "number">0</span>
						<span>-</span>
						<span class = "number">1</span>
						<span class = "number">2</span>
						<span class = "number">0</span>
						<span class = "number">3</span>
						<span>-</span>
						<span class = "number">1</span>
						<span class = "number">6</span>
						<span class = "number">2</span>
						<span class = "number">7</span>
					</div>
					<div class = "name">
						<span class = "symbol">Д</span>
						<span class = "symbol">е</span>
						<span class = "symbol">н</span>
						<span class = "symbol">и</span>
						<span class = "symbol">с</span>
						<span> </span>
						<span class = "symbol">А</span>
						<span class = "symbol">л</span>
						<span class = "symbol">е</span>
						<span class = "symbol">к</span>
						<span class = "symbol">с</span>
						<span class = "symbol">а</span>
						<span class = "symbol">н</span>
						<span class = "symbol">д</span>
						<span class = "symbol">р</span>
						<span class = "symbol">о</span>
						<span class = "symbol">в</span>
						<span class = "symbol">и</span>
						<span class = "symbol">ч</span>
						<span> </span>
						<span class = "symbol">Г</span>
						<span class = "symbol">.</span>
					</div>
				</div>
			</div>
		<?php }

	}